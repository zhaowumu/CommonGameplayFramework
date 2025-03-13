// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameUISubsystem.h"

#include "Engine/GameInstance.h"
#include "GameFramework/HUD.h"
#include "GameUIPolicy.h"
#include "PrimaryGameLayout.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "CommonGameplay/System/CommonGameplayTags.h"

UCommonGameUISubsystem::UCommonGameUISubsystem()
{
}

void UCommonGameUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	/*
	 * AddTicker 用于注册一个定时任务，这里的任务是 调用 Tick 方法，并且 0.0f 的参数表示每帧都会执行（即不按时间间隔延迟）。
	 */
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UCommonGameUISubsystem::Tick), 0.0f);
}

void UCommonGameUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	// 移除定时任务
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

UCommonDesktop* UCommonGameUISubsystem::ShowDesktopByClass(const ULocalPlayer* LocalPlayer,
                                                       TSubclassOf<UCommonDesktop> DesktopClass)
{
	if (!DesktopClass)
	{
		return nullptr;
	}

	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return nullptr;
	}

	if (UPrimaryGameLayout* RootLayout = GetPlayerGameLayout(LocalPlayer))
	{
		// 移除以前的 Desktop
		RootLayout->RemoveDesktopWidget(DesktopClass);
		UCommonDesktop* Desktop = Cast<UCommonDesktop>(
			RootLayout->PushWidgetToLayerStack(CommonGameplayTags::Fei_UI_Layer_Game, DesktopClass));
		return Desktop;
	}

	return nullptr;
}

void UCommonGameUISubsystem::HideDesktopByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonDesktop> DesktopClass)
{
	if (!DesktopClass)
	{
		return;
	}

	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return;
	}

	if (UPrimaryGameLayout* RootLayout = GetPlayerGameLayout(LocalPlayer))
	{
		// 移除以前的 Desktop
		RootLayout->RemoveDesktopWidget(DesktopClass);
	}
}

UCommonWindow* UCommonGameUISubsystem::ShowWindowByClass(const ULocalPlayer* LocalPlayer,
                                                     TSubclassOf<UCommonWindow> WindowClass)
{
	if (!WindowClass)
	{
		return nullptr;
	}

	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return nullptr;
	}

	if (UCommonDesktop* Desktop = GetPlayerDesktop(LocalPlayer))
	{
		Desktop->ShowWindowByClass(WindowClass);
	}
	return nullptr;
}

void UCommonGameUISubsystem::HideWindowByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonWindow> WindowClass)
{
	if (!WindowClass)
	{
		return;
	}

	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return;
	}

	if (UCommonDesktop* Desktop = GetPlayerDesktop(LocalPlayer))
	{
		Desktop->HideWindowByClass(WindowClass);
	}
}

UCommonPanel* UCommonGameUISubsystem::ShowPanelByClass(const ULocalPlayer* LocalPlayer,
	TSubclassOf<UCommonPanel> PanelClass)
{
	if (!PanelClass)
	{
		return nullptr;
	}

	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return nullptr;
	}

	if (UPrimaryGameLayout* RootLayout = GetPlayerGameLayout(LocalPlayer))
	{
		// 移除以前的 Desktop
		UCommonPanel* Panel = Cast<UCommonPanel>(
			RootLayout->PushWidgetToLayerStack(CommonGameplayTags::Fei_UI_Layer_Panel, PanelClass));
		return Panel;
	}

	return nullptr;
}

void UCommonGameUISubsystem::HidePanelWithByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonPanel> PanelClass)
{
	if (!PanelClass)
	{
		return;
	}
	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return;
	}

	if (UPrimaryGameLayout* RootLayout = GetPlayerGameLayout(LocalPlayer))
	{
		// 移除以前的 Desktop
		RootLayout->RemovePanelWidget(PanelClass);
	}
}

void UCommonGameUISubsystem::PopPanel(const ULocalPlayer* LocalPlayer)
{
	// 如果没有传入LocalPlayer，那就使用第一个本地玩家
	if (!LocalPlayer)
	{
		LocalPlayer = GetGameInstance()->GetFirstGamePlayer();
	}

	if (!LocalPlayer)
	{
		return;
	}

	if (UPrimaryGameLayout* RootLayout = GetPlayerGameLayout(LocalPlayer))
	{
		// 移除以前的 Desktop
		RootLayout->PopPanelWidget();
	}
}


bool UCommonGameUISubsystem::Tick(float DeltaTime)
{
	SyncRootLayoutVisibilityToShowHUD();

	return true;
}

void UCommonGameUISubsystem::SyncRootLayoutVisibilityToShowHUD()
{
	// 获取当前 UIPolicy
	if (const UGameUIPolicy* Policy = GetCurrentUIPolicy())
	{
		// 遍历所有本地玩家
		for (const ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
		{
			bool bShouldShowUI = true;

			// 获取玩家控制器
			if (const APlayerController* PC = LocalPlayer->GetPlayerController(GetWorld()))
			{
				const AHUD* HUD = PC->GetHUD();

				if (HUD && !HUD->bShowHUD)
				{
					// 同步 显示状态
					bShouldShowUI = false;
				}
			}

			// 获取 RootLayout
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
			{
				// 同步显示状态
				const ESlateVisibility DesiredVisibility = bShouldShowUI
					                                           ? ESlateVisibility::SelfHitTestInvisible
					                                           : ESlateVisibility::Collapsed;
				if (DesiredVisibility != RootLayout->GetVisibility())
				{
					RootLayout->SetVisibility(DesiredVisibility);
				}
			}
		}
	}
}

