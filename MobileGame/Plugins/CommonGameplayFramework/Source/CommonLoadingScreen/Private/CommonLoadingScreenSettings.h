// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/SoftObjectPath.h"

#include "CommonLoadingScreenSettings.generated.h"

class UObject;

/**
 * Settings for a loading screen system.
 */
UCLASS(config=CommonGameplaySetting, defaultconfig)
class UCommonLoadingScreenSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UCommonLoadingScreenSettings();

	virtual FName GetCategoryName() const override
	{
		return FName("Game");
	};

public:
	// The widget to load for the loading screen.
	UPROPERTY(config, EditAnywhere, Category=LoadingScreen, meta=(MetaClass="/Script/UMG.UserWidget"))
	FSoftClassPath LoadingScreenWidget;

	// The z-order of the loading screen widget in the viewport stack
	UPROPERTY(config, EditAnywhere, Category=LoadingScreen)
	int32 LoadingScreenZOrder = 10000;

	// How long to hold the loading screen up after other loading finishes (in seconds) to
	// try to give texture streaming a chance to avoid blurriness
	// 在其他加载完成后，将加载屏幕保持多长时间（以秒为单位）尝试给纹理流一个避免模糊的机会
	// Note: This is not normally applied in the editor for iteration time, but can be 
	// enabled via HoldLoadingScreenAdditionalSecsEvenInEditor
	UPROPERTY(config, EditAnywhere, Category=LoadingScreen,
		meta=(ForceUnits=s))
	float HoldLoadingScreenAdditionalSecs = 2.0f;

	// The interval in seconds beyond which the loading screen is considered permanently hung (if non-zero).
	// 加载屏幕被视为永久挂起的时间间隔（秒）（如果非零）。
	UPROPERTY(EditAnywhere, Category=LoadingScreen, meta=(ForceUnits=s))
	float LoadingScreenHeartbeatHangDuration = 0.0f;

	// The interval in seconds between each log of what is keeping a loading screen up (if non-zero).
	// 保持加载屏幕打开的每个日志之间的间隔（秒）（如果非零）。
	UPROPERTY(EditAnywhere, Category=LoadingScreen, meta=(ForceUnits=s))
	float LogLoadingScreenHeartbeatInterval = 1.0f;

	/*// When true, the reason the loading screen is shown or hidden will be printed to the log every frame.
	// 当为真时，显示或隐藏加载屏幕的原因将打印到日志中。
	UPROPERTY(Transient, EditAnywhere, Category=LoadingScreen,
		meta=(ConsoleVariable="CommonLoadingScreen.LogLoadingScreenReasonEveryFrame"))
	bool LogLoadingScreenReasonEveryFrame = 0;*/

	/*// Force the loading screen to be displayed (useful for debugging)
	// 强制显示加载屏幕（用于调试）
	UPROPERTY(Transient, EditAnywhere, Category=LoadingScreen, meta=(ConsoleVariable="CommonLoadingScreen.AlwaysShow"))
	bool ForceLoadingScreenVisible = false;*/

	/*// Should we apply the additional HoldLoadingScreenAdditionalSecs delay even in the editor
	// (useful when iterating on loading screens)
	UPROPERTY(Transient, EditAnywhere, Category=LoadingScreen)
	bool HoldLoadingScreenAdditionalSecsEvenInEditor = false;*/

	// Should we apply the additional HoldLoadingScreenAdditionalSecs delay even in the editor
	// 我们是否应该在编辑器中应用额外的HoldLoadingScreenAdditional Secs延迟
	// (useful when iterating on loading screens)在加载屏幕上迭代时很有用）
	UPROPERTY(EditAnywhere, Category=LoadingScreen)
	bool ForceTickLoadingScreenEvenInEditor = true;
};
