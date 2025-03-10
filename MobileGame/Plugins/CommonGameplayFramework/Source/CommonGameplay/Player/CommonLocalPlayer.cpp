// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonLocalPlayer.h"

#include "CommonGameplay/GameSettings/CommonLocalSettings.h"
#include "CommonGameplay/GameSettings/CommonSharedSettings.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "CommonGameplay/UI/GameUIManagerSubsystem.h"
#include "CommonGameplay/UI/GameUIPolicy.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonLocalPlayer)

class APawn;
class APlayerState;
class FViewport;
struct FSceneViewProjectionData;

UCommonLocalPlayer::UCommonLocalPlayer()
	: Super(FObjectInitializer::Get())
{
}

FDelegateHandle UCommonLocalPlayer::CallAndRegister_OnPlayerControllerSet(
	FPlayerControllerSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());

	if (PC)
	{
		Delegate.Execute(this, PC);
	}

	return OnPlayerControllerSet.Add(Delegate);
}

FDelegateHandle UCommonLocalPlayer::CallAndRegister_OnPlayerStateSet(FPlayerStateSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());
	APlayerState* PlayerState = PC ? PC->PlayerState : nullptr;

	if (PlayerState)
	{
		Delegate.Execute(this, PlayerState);
	}

	return OnPlayerStateSet.Add(Delegate);
}

FDelegateHandle UCommonLocalPlayer::CallAndRegister_OnPlayerPawnSet(FPlayerPawnSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());
	APawn* Pawn = PC ? PC->GetPawn() : nullptr;

	if (Pawn)
	{
		Delegate.Execute(this, Pawn);
	}

	return OnPlayerPawnSet.Add(Delegate);
}

UCommonLocalSettings* UCommonLocalPlayer::GetLocalSettings() const
{
	return UCommonLocalSettings::Get();
}

UCommonSharedSettings* UCommonLocalPlayer::GetSharedSettings() const
{
	if (!SharedSettings)
	{
		// On PC it's okay to use the sync load because it only checks the disk
		// 在PC上，使用同步加载是可以的，因为它只检查磁盘
		// This could use a platform tag to check for proper save support instead
		// 可以使用平台标签来检查是否支持正确的保存
		bool bCanLoadBeforeLogin = PLATFORM_DESKTOP;

		// 如果是桌面平台，则可以在登录之前加载设置
		if (bCanLoadBeforeLogin)
		{
			SharedSettings = UCommonSharedSettings::LoadOrCreateSettings(this);
		}
		else
		{
			// 需要等待用户登录以获取真实设置，因此返回临时设置
			SharedSettings = UCommonSharedSettings::CreateTemporarySettings(this);
		}
	}

	return SharedSettings;
}

bool UCommonLocalPlayer::GetProjectionData(FViewport* Viewport, FSceneViewProjectionData& ProjectionData,
                                           int32 StereoViewIndex) const
{
	if (!bIsPlayerViewEnabled)
	{
		return false;
	}

	return Super::GetProjectionData(Viewport, ProjectionData, StereoViewIndex);
}

UPrimaryGameLayout* UCommonLocalPlayer::GetRootUILayout() const
{
	if (UGameUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			return Policy->GetRootLayout(this);
		}
	}

	return nullptr;
}
