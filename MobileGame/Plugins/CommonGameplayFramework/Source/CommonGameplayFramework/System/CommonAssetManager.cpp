// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonAssetManager.h"

#include "CommonLogChannels.h"

UCommonAssetManager::UCommonAssetManager()
{
}

UCommonAssetManager& UCommonAssetManager::Get()
{
	check(GEngine);

	if (UCommonAssetManager* Singleton = Cast<UCommonAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogCommon, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to CommonAssetManager!"));

	// Fatal error above prevents this from being called.
	return *NewObject<UCommonAssetManager>();
}

void UCommonAssetManager::DumpLoadedAssets()
{
	UE_LOG(LogCommon, Log, TEXT("========== Start Dumping Loaded Assets =========="));

	for (const UObject* LoadedAsset : Get().LoadedAssets)
	{
		UE_LOG(LogCommon, Log, TEXT("  %s"), *GetNameSafe(LoadedAsset));
	}

	UE_LOG(LogCommon, Log, TEXT("... %d assets in loaded pool"), Get().LoadedAssets.Num());
	UE_LOG(LogCommon, Log, TEXT("========== Finish Dumping Loaded Assets =========="));
}

UObject* UCommonAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		// 创建日志对象（如果需要记录加载时间）
		TUniquePtr<FScopeLogTime> LogTimePtr;

		if (ShouldLogAssetLoads())
		{
			// 是一个作用域定时器对象，当超出作用域时，它会自动计算并输出耗时，帮助开发者优化加载性能。
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// Use LoadObject if asset manager isn't ready yet.如果 AssetManager 还未初始化，则使用 TryLoad 直接加载资源
		// 内部会调用 LoadObject<UObject> 来加载资源。它不会经过 UAssetManager 的管理，而是直接从磁盘或内存加载资源。
		return AssetPath.TryLoad();
	}

	return nullptr;
}

bool UCommonAssetManager::ShouldLogAssetLoads()
{
	// FCommandLine::Get() 获取游戏的启动参数字符串（即执行游戏时的命令行参数）。如果在命令行中加入 -LogAssetLoads，那么 bLogAssetLoads 将被设置为 true，否则为 false。
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

void UCommonAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}

void UCommonAssetManager::StartInitialLoading()
{
	// 宏 SCOPED_BOOT_TIMING 用于 性能分析（profiling），记录 StartInitialLoading 方法执行时间，方便分析启动性能。
	SCOPED_BOOT_TIMING("UCommonAssetManager::StartInitialLoading");

	// This does all of the scanning, need to do this now even if loads are deferred.进行基础扫描和加载。
	Super::StartInitialLoading();

	// TODO 这里没有使用官方的FLyraAssetManagerStartupJob
	InitializeGameplayCueManager();
	
	/*
	STARTUP_JOB(InitializeGameplayCueManager());
	{
		// Load base game data asset
		STARTUP_JOB_WEIGHTED(GetGameData(), 25.f);
	}

	// Run all the queued up startup jobs.运行 所有已排队的启动任务（包括 InitializeGameplayCueManager 和 GetGameData()）。
	DoAllStartupJobs();*/
}


#if WITH_EDITOR
void UCommonAssetManager::PreBeginPIE(bool bStartSimulate)
{
	Super::PreBeginPIE(bStartSimulate);

	{
		// FScopedSlowTask 是 Unreal Engine 提供的一个 进度反馈机制，在 PIE 启动前 显示一个 "Loading PIE Data" 的进度窗口。
		FScopedSlowTask SlowTask(0, NSLOCTEXT("CommonEditor", "BeginLoadingPIEData", "Loading PIE Data"));
		const bool bShowCancelButton = false;
		const bool bAllowInPIE = true;
		SlowTask.MakeDialog(bShowCancelButton, bAllowInPIE);

		// const ULyraGameData& LocalGameDataCommon = GetGameData();

		// Intentionally after GetGameData to avoid counting GameData time in this timer
		SCOPE_LOG_TIME_IN_SECONDS(TEXT("PreBeginPIE asset preloading complete"), nullptr);

		// You could add preloading of anything else needed for the experience we'll be using here
		// (e.g., by grabbing the default experience from the world settings + the experience override in developer settings)
	}
}
#endif


UPrimaryDataAsset* UCommonAssetManager::LoadGameDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass, const TSoftObjectPtr<UPrimaryDataAsset>& DataClassPath, FPrimaryAssetType PrimaryAssetType)
{
	UPrimaryDataAsset* Asset = nullptr;

	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("Loading GameData Object"), STAT_GameData, STATGROUP_LoadTime);
	if (!DataClassPath.IsNull())
	{
#if WITH_EDITOR
		FScopedSlowTask SlowTask(0, FText::Format(NSLOCTEXT("LyraEditor", "BeginLoadingGameDataTask", "Loading GameData {0}"), FText::FromName(DataClass->GetFName())));
		const bool bShowCancelButton = false;
		const bool bAllowInPIE = true;
		SlowTask.MakeDialog(bShowCancelButton, bAllowInPIE);
#endif
		UE_LOG(LogCommon, Log, TEXT("Loading GameData: %s ..."), *DataClassPath.ToString());
		SCOPE_LOG_TIME_IN_SECONDS(TEXT("    ... GameData loaded!"), nullptr);

		// This can be called recursively in the editor because it is called on demand from PostLoad so force a sync load for primary asset and async load the rest in that case
		if (GIsEditor)
		{
			Asset = DataClassPath.LoadSynchronous();
			LoadPrimaryAssetsWithType(PrimaryAssetType);
		}
		else
		{
			TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
			if (Handle.IsValid())
			{
				Handle->WaitUntilComplete(0.0f, false);

				// This should always work
				Asset = Cast<UPrimaryDataAsset>(Handle->GetLoadedAsset());
			}
		}
	}

	if (Asset)
	{
		GameDataMap.Add(DataClass, Asset);
	}
	else
	{
		// It is not acceptable to fail to load any GameData asset. It will result in soft failures that are hard to diagnose.
		UE_LOG(LogCommon, Fatal, TEXT("Failed to load GameData asset at %s. Type %s. This is not recoverable and likely means you do not have the correct data to run %s."), *DataClassPath.ToString(), *PrimaryAssetType.ToString(), FApp::GetProjectName());
	}

	return Asset;
}

void UCommonAssetManager::InitializeGameplayCueManager()
{
	SCOPED_BOOT_TIMING("ULyraAssetManager::InitializeGameplayCueManager");
	

	/*ULyraGameplayCueManager* GCM = ULyraGameplayCueManager::Get();
	check(GCM);
	GCM->LoadAlwaysLoadedCues();*/
}

void UCommonAssetManager::UpdateInitialGameContentLoadPercent(float GameContentPercent)
{
	// Could route this to the early startup loading screen
}


