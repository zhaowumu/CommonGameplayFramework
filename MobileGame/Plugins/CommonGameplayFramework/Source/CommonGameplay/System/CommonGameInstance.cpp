// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonGameInstance.h"


#include "ChunkDownloader.h"
#include "ChunkDownloader.h"
#include "CommonLogChannels.h"
#include "CommonSessionSubsystem.h"
#include "CommonUISettings.h"
#include "CommonUserSubsystem.h"
#include "HttpModule.h"
#include "ICommonUIModule.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "CommonGameplay/UI/CommonGameUISubsystem.h"
#include "CommonGameplay/UI/GameUIManagerSubsystem.h"
#include "CommonGameplay/UI/Messaging/CommonGameDialog.h"
#include "CommonGameplay/Utils/CommonFunctionLibrary.h"
#include "Interfaces/IHttpResponse.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonGameInstance)

UCommonGameInstance::UCommonGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCommonGameInstance::HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message)
{
	ULocalPlayer* FirstPlayer = GetFirstGamePlayer();
	// Forward severe ones to the error dialog for the first player
	// 如果消息类型是错误类型，它会将错误消息显示给第一个玩家。
	if (FirstPlayer && MessageType.MatchesTag(FCommonUserTags::SystemMessage_Error))
	{
		if (UCommonLocalPlayerSubsystem* Subsystem = FirstPlayer->GetSubsystem<UCommonLocalPlayerSubsystem>())
		{
			Subsystem->ShowError(UCommonGameDialogDescriptor::CreateConfirmationOk(Title, Message));
		}
	}
}

void UCommonGameInstance::HandlePrivilegeChanged(const UCommonUserInfo* UserInfo, ECommonUserPrivilege Privilege,
                                                 ECommonUserAvailability OldAvailability,
                                                 ECommonUserAvailability NewAvailability)
{
	// By default show errors and disconnect if play privilege for first player is lost
	// 如果玩家权限被取消，则显示错误消息并断开连接。
	if (Privilege == ECommonUserPrivilege::CanPlay && OldAvailability == ECommonUserAvailability::NowAvailable &&
		NewAvailability != ECommonUserAvailability::NowAvailable)
	{
		UE_LOG(LogCommon, Error, TEXT("HandlePrivilegeChanged: Player %d no longer has permission to play the game!"),
		       UserInfo->LocalPlayerIndex);
		// TODO: Games can do something specific in subclass
		// ReturnToMainMenu();
	}
}

void UCommonGameInstance::HandlerUserInitialized(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error,
                                                 ECommonUserPrivilege RequestedPrivilege,
                                                 ECommonUserOnlineContext OnlineContext)
{
	// Subclasses can override this
}

int32 UCommonGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		if (!PrimaryPlayer.IsValid())
		{
			UE_LOG(LogCommon, Log, TEXT("AddLocalPlayer: Set %s to Primary Player"), *NewPlayer->GetName());
			PrimaryPlayer = NewPlayer;
		}

		GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerAdded(Cast<UCommonLocalPlayer>(NewPlayer));
	}

	return ReturnVal;
}

bool UCommonGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	if (PrimaryPlayer == ExistingPlayer)
	{
		//TODO: do we want to fall back to another player?
		PrimaryPlayer.Reset();
		UE_LOG(LogCommon, Log, TEXT("RemoveLocalPlayer: Unsetting Primary Player from %s"), *ExistingPlayer->GetName());
	}
	GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerDestroyed(Cast<UCommonLocalPlayer>(ExistingPlayer));

	return Super::RemoveLocalPlayer(ExistingPlayer);
}

void UCommonGameInstance::Init()
{
	Super::Init();
	PatchingState = FString::Printf(TEXT("Init Game..."));
	OnInitGameMessage.Broadcast(PatchingState);
	//UpdateServerProjectVersion();

	// After subsystems are initialized, hook them together
	FGameplayTagContainer PlatformTraits = ICommonUIModule::GetSettings().GetPlatformTraits();

	UCommonUserSubsystem* UserSubsystem = GetSubsystem<UCommonUserSubsystem>();
	if (ensure(UserSubsystem))
	{
		UserSubsystem->SetTraitTags(PlatformTraits);
		UserSubsystem->OnHandleSystemMessage.AddDynamic(this, &UCommonGameInstance::HandleSystemMessage);
		UserSubsystem->OnUserPrivilegeChanged.AddDynamic(this, &UCommonGameInstance::HandlePrivilegeChanged);
		UserSubsystem->OnUserInitializeComplete.AddDynamic(this, &UCommonGameInstance::HandlerUserInitialized);
	}

	UCommonSessionSubsystem* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
	if (ensure(SessionSubsystem))
	{
		SessionSubsystem->OnUserRequestedSessionEvent.AddUObject(this, &UCommonGameInstance::OnUserRequestedSession);
		SessionSubsystem->OnDestroySessionRequestedEvent.AddUObject(
			this, &UCommonGameInstance::OnDestroySessionRequested);
	}

	GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red,"FFFFFFFFFFFFFFFFFFssssssssssss");
}

void UCommonGameInstance::Shutdown()
{
	Super::Shutdown();
	//关闭ChunkDownloader
	FChunkDownloader::Shutdown();
}

void UCommonGameInstance::ResetUserAndSessionState()
{
	UCommonUserSubsystem* UserSubsystem = GetSubsystem<UCommonUserSubsystem>();
	if (ensure(UserSubsystem))
	{
		UserSubsystem->ResetUserState();
	}

	UCommonSessionSubsystem* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
	if (ensure(SessionSubsystem))
	{
		SessionSubsystem->CleanUpSessions();
	}
}

void UCommonGameInstance::ReturnToMainMenu()
{
	// By default when returning to main menu we should reset everything
	ResetUserAndSessionState();

	Super::ReturnToMainMenu();
}

void UCommonGameInstance::UpdateServerProjectVersion()
{
	UE_LOG(LogCommon, Log, TEXT("UpdateServerProjectVersion: Requesting server version..."))
	PatchingState = FString::Printf(TEXT("Request Server Version"));
	OnInitGameMessage.Broadcast(PatchingState);

	FString URL = TEXT("http://127.0.0.1/GameCDN/Version.txt"); // 替换为你的 TXT 链接

	// 创建 HTTP 请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UCommonGameInstance::OnServerVersionReceived);
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UCommonGameInstance::OnServerVersionReceived(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                  bool bWasSuccessful)
{
	PatchingState = FString::Printf(TEXT("Received Server Version"));
	OnInitGameMessage.Broadcast(PatchingState);

	if (bWasSuccessful)
	{
		// 获取响应内容

		FString ResponseContent = Response.Get()->GetContentAsString();

		// 如果首字符不是1
		if (ResponseContent[0] != '1')
		{
			OnInitGameComplete.Broadcast(false);
			return;
		}

		ServerVersion = ResponseContent;
		FString CurrentVersion = UCommonFunctionLibrary::GetProjectVersion();
		UE_LOG(LogCommon, Log, TEXT("Version: %s[server] >> %s[current]"), *ServerVersion, *CurrentVersion);
		if (ServerVersion == CurrentVersion)
		{
			OnInitGameComplete.Broadcast(true);
		}
		else
		{
			InitChunkData();
		}
	}
	else
	{
		PatchingState = FString::Printf(TEXT("Cannot Get Server Version"));
		OnInitGameMessage.Broadcast(PatchingState);
		OnInitGameComplete.Broadcast(false);
	}
}

void UCommonGameInstance::InitChunkData()
{
	PatchingState = FString::Printf(TEXT("Init Chunk Manifest"));
	OnInitGameMessage.Broadcast(PatchingState);

	// 这个和DefaultGame.ini里面的对应 [/Script/Plugins.ChunkDownloader PitchPak]
	const FString DeploymentName = "PitchPak";
	// 这个是版本ID，和BuildManifest-Windows.txt里面的 $BUILD_ID = 1.0.0.1 对应 
	const FString ContentBuildId = ServerVersion;

	// 打印ContentBuildId
	UE_LOG(LogCommon, Log, TEXT("Chunk Manifest ContentBuildId: %s"), *ContentBuildId)

	// 用选定平台初始化文件块下载器
	TSharedRef<FChunkDownloader> Downloader = FChunkDownloader::GetOrCreate();
	Downloader->Initialize("Windows", 8);
	// TODO 安卓下载方式
	// Downloader->Initialize("Android", 8);


	//加载缓存的版本ID，这将检查磁盘上是否已经下载文件，如果它们是最新清单文件，则ChunkDownloader可以跳过下载流程。
	Downloader->LoadCachedBuild(DeploymentName);

	//更新版本清单文件
	TFunction<void(bool bSuccess)> UpdateManifestCompleteCallback = [&](bool bSuccess)
	{
		OnChunkManifestUpdateOver(bSuccess);
	};
	// Manifest文件更新完成会执行OnManifestUpdateComplete回调
	Downloader->UpdateBuild(DeploymentName, ContentBuildId, UpdateManifestCompleteCallback);
}

bool UCommonGameInstance::PatchGame()
{
	UE_LOG(LogCommon, Warning, TEXT("Patch Game...>> %d"), ChunkDownloadList.Num())
	PatchingState = FString::Printf(TEXT("Patch Game"));
	OnInitGameMessage.Broadcast(PatchingState);

	//确保下载清单是最新的
	if (bIsDownloadManifestUpdate)
	{
		IsPatching = true;

		//获取文件块下载器
		TSharedRef<FChunkDownloader> Downloader = FChunkDownloader::GetChecked();

		TArray<int32> TempChunkIds;
		Downloader->GetAllChunkIds(TempChunkIds);

		ChunkDownloadList = TempChunkIds;

		//报告当前文件块状态
		for (int32 ChunkID : ChunkDownloadList)
		{
			int32 ChunkStatus = static_cast<int32>(Downloader->GetChunkStatus(ChunkID));
			UE_LOG(LogCommon, Log, TEXT("Chunk %i status: %i"), ChunkID, ChunkStatus);
		}


		TFunction<void (bool bSuccess)> LoadingModeCompleteCallback = [&](bool bSuccess)
		{
			// 当所有文件块完成下载
			OnChunkLoadingModeOver(bSuccess);
		};
		// 监听启动加载模式，可以在不调用加载模式的情况下在后台被动下载文件块，使用它将输出下载统计信息，使你可以创建一个可以跟踪用户下载进度的UI
		Downloader->BeginLoadingMode(LoadingModeCompleteCallback);

		TFunction<void (bool bSuccess)> DownloadCompleteCallback = [&](bool bSuccess)
		{
			// 所有文件块完成下载完成
			OnChunkDownloadOver(bSuccess);
		};
		// 下载文件块
		Downloader->DownloadChunks(ChunkDownloadList, DownloadCompleteCallback, 1);

		return true;
	}

	// 我们无法联系服务器验证清单，因此你无法修补
	UE_LOG(LogTemp, Error, TEXT("Manifest Update Failed.Can't patch the game"));
	PatchingState = FString::Printf(TEXT("Manifest Update Failed.Can't patch the game"));
	OnInitGameMessage.Broadcast(PatchingState);

	return false;
}

void UCommonGameInstance::GetChunkLoadingProgress(int32& BytesDownloaded, int32& TotalBytesToDownload,
                                                  float& DownloadPercent, int32& ChunksMounted,
                                                  int32& TotalChunksToMount,
                                                  float& MountPercent) const
{
	//获取ChunkDownloader的引用
	TSharedRef<FChunkDownloader> Downloader = FChunkDownloader::GetChecked();

	//获取加载统计结构体
	FChunkDownloader::FStats LoadingStats = Downloader->GetLoadingStats();

	//获取已下载和要下载的的字节
	BytesDownloaded = LoadingStats.BytesDownloaded;
	TotalBytesToDownload = LoadingStats.TotalBytesToDownload;

	//获取已挂载文件块数和要下载的文件块数
	ChunksMounted = LoadingStats.ChunksMounted;
	TotalChunksToMount = LoadingStats.TotalChunksToMount;

	//使用以上统计信息计算下载和挂载百分比
	DownloadPercent = ((float)BytesDownloaded / (float)TotalBytesToDownload) * 100.0f;
	MountPercent = ((float)ChunksMounted / (float)TotalChunksToMount) * 100.0f;
}

void UCommonGameInstance::OnChunkManifestUpdateOver(bool bSuccess)
{
	bIsDownloadManifestUpdate = bSuccess;

	PatchingState = FString::Printf(TEXT("Update Chunk Manifest Over"));
	OnInitGameMessage.Broadcast(PatchingState);
	UE_LOG(LogCommon, Warning, TEXT("Manifest Update %s"), bSuccess ? TEXT("Succeeded") : TEXT("Failed"));

	if (bIsDownloadManifestUpdate)
	{
		PatchGame();
	}
	OnChunkManifestComplete.Broadcast(bSuccess);
}

void UCommonGameInstance::OnChunkDownloadOver(bool bSuccess)
{
	if (bSuccess)
	{
		PatchingState = FString::Printf(TEXT("Download Chunk complete"));
		OnInitGameMessage.Broadcast(PatchingState);
		UE_LOG(LogCommon, Warning, TEXT("Download Chunk complete"));

		//获取文件块下载器
		TSharedRef<FChunkDownloader> Downloader = FChunkDownloader::GetChecked();
		FJsonSerializableArrayInt DownloadedChunks;

		for (int32 ChunkID : ChunkDownloadList)
		{
			DownloadedChunks.Add(ChunkID);
		}

		//挂载文件块
		TFunction<void(bool IsSuccess)> MountCompleteCallback = [&](bool IsSuccess)
		{
			OnChunkMountOver(IsSuccess);
		};
		Downloader->MountChunks(DownloadedChunks, MountCompleteCallback);

		OnChunkDownloadComplete.Broadcast(true);
	}
	else
	{
		UE_LOG(LogCommon, Display, TEXT("Download Chunk failed"));
		PatchingState = FString::Printf(TEXT("Download Chunk failed"));
		OnInitGameMessage.Broadcast(PatchingState);
		//调用委托
		OnChunkDownloadComplete.Broadcast(false);
	}
}

void UCommonGameInstance::OnChunkLoadingModeOver(bool bSuccess)
{
	IsPatching = false;
	// 监听下载状态完成
	UE_LOG(LogTemp, Warning, TEXT("Loading Mode complete %d"), bSuccess)
	PatchingState = FString::Printf(TEXT("Loading Mode complete"));
	OnInitGameMessage.Broadcast(PatchingState);

	OnInitGameComplete.Broadcast(bSuccess);
}

void UCommonGameInstance::OnChunkMountOver(bool bSuccess)
{
	// 单个pak挂载
	UE_LOG(LogCommon, Warning, TEXT("Chunk Mount complete %d"), bSuccess)
	PatchingState = FString::Printf(TEXT("Chunk Mount complete"));
	OnInitGameMessage.Broadcast(PatchingState);
	OnChunkMountComplete.Broadcast(bSuccess);
	//OnInitGameComplete.Broadcast(bSuccess);
}

void UCommonGameInstance::OnUserRequestedSession(const FPlatformUserId& PlatformUserId,
                                                 UCommonSession_SearchResult* InRequestedSession,
                                                 const FOnlineResultInformation& RequestedSessionResult)
{
	// 如何会话有效
	if (InRequestedSession)
	{
		SetRequestedSession(InRequestedSession);
	}
	else
	{
		HandleSystemMessage(FCommonUserTags::SystemMessage_Error,
		                    NSLOCTEXT("CommonGame", "Warning_RequestedSessionFailed", "Requested Session Failed"),
		                    RequestedSessionResult.ErrorText);
	}
}

void UCommonGameInstance::OnDestroySessionRequested(const FPlatformUserId& PlatformUserId, const FName& SessionName)
{
	// When a session destroy is requested, please make sure that your project is in the right state to destroy the session and transition out of it
	// 当请求销毁会话时，请确保您的项目处于正确的状态，可以销毁会话并从中转换出来

	UE_LOG(LogCommon, Verbose, TEXT("[%hs] PlatformUserId:%d, SessionName: %s)"), __FUNCTION__,
	       PlatformUserId.GetInternalId(), *SessionName.ToString());

	ReturnToMainMenu();
}

void UCommonGameInstance::SetRequestedSession(UCommonSession_SearchResult* InRequestedSession)
{
	RequestedSession = InRequestedSession;
	if (RequestedSession)
	{
		if (CanJoinRequestedSession())
		{
			JoinRequestedSession();
		}
		else
		{
			ResetGameAndJoinRequestedSession();
		}
	}
}

bool UCommonGameInstance::CanJoinRequestedSession() const
{
	// Default behavior is always allow joining the requested session
	return true;
}

void UCommonGameInstance::JoinRequestedSession()
{
	if (RequestedSession)
	{
		if (ULocalPlayer* const FirstPlayer = GetFirstGamePlayer())
		{
			UCommonSessionSubsystem* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
			if (ensure(SessionSubsystem))
			{
				// Clear our current requested session since we are now acting on it.
				UCommonSession_SearchResult* LocalRequestedSession = RequestedSession;
				RequestedSession = nullptr;
				SessionSubsystem->JoinSession(FirstPlayer->PlayerController, LocalRequestedSession);
			}
		}
	}
}

void UCommonGameInstance::ResetGameAndJoinRequestedSession()
{
	// Default behavior is to return to the main menu.  The game must call JoinRequestedSession when the game is in a ready state.
	ReturnToMainMenu();
}


//void UCommonGameInstance::OnPreLoadMap(const FString& MapName)
//{
//	if (!IsDedicatedServerInstance())
//	{
//		if (!bWasInLoadMap)
//		{
//			UGameUIManagerSubsystem* UIManager = GetSubsystem<UGameUIManagerSubsystem>();
//			for (ULocalPlayer* LocalPlayer : LocalPlayers)
//			{
//				UIManager->NotifyPlayerAdded(Cast<UCommonLocalPlayer>(LocalPlayer));
//			}
//		}
//	}
//}
