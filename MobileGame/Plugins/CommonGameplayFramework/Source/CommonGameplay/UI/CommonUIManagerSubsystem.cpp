// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUIManagerSubsystem.h"

#include "Engine/GameInstance.h"
#include "GameFramework/HUD.h"
#include "GameUIPolicy.h"
#include "PrimaryGameLayout.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"

UCommonUIManagerSubsystem::UCommonUIManagerSubsystem()
{
}

void UCommonUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	/*
	 * AddTicker 用于注册一个定时任务，这里的任务是 调用 Tick 方法，并且 0.0f 的参数表示每帧都会执行（即不按时间间隔延迟）。
	 */
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UCommonUIManagerSubsystem::Tick), 0.0f);
}

void UCommonUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// 移除定时任务
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UCommonUIManagerSubsystem::Tick(float DeltaTime)
{
	SyncRootLayoutVisibilityToShowHUD();
	
	return true;
}

void UCommonUIManagerSubsystem::SyncRootLayoutVisibilityToShowHUD()
{
	// 获取当前 UIPolicy
	if (const UGameUIPolicy* Policy = GetCurrentUIPolicy())
	{
		// 遍历所有本地玩家
		for (const ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
		{
			bool bShouldShowUI = true;
			
			if (const APlayerController* PC = LocalPlayer->GetPlayerController(GetWorld()))
			{
				const AHUD* HUD = PC->GetHUD();

				if (HUD && !HUD->bShowHUD)
				{
					bShouldShowUI = false;
				}
			}

			// 获取 RootLayout
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
			{
				// 同步显示状态
				const ESlateVisibility DesiredVisibility = bShouldShowUI ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
				if (DesiredVisibility != RootLayout->GetVisibility())
				{
					RootLayout->SetVisibility(DesiredVisibility);	
				}
			}
		}
	}
}
