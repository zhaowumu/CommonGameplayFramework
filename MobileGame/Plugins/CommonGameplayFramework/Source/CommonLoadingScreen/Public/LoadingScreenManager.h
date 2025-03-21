// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "UObject/WeakInterfacePtr.h"
#include "LoadingScreenManager.generated.h"

template <typename InterfaceType> class TScriptInterface;

class FSubsystemCollectionBase;
class IInputProcessor;
class ILoadingProcessInterface;
class SWidget;
class UObject;
class UWorld;
struct FFrame;
struct FWorldContext;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreLoadMapTriggered, const FString&, MapName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostLoadMapTriggered, const FString&, MapName);


/**
 * 加载屏幕管理器
 */
UCLASS()
class COMMONLOADINGSCREEN_API ULoadingScreenManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~End of USubsystem interface

	//~FTickableObjectBase interface
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	//~End of FTickableObjectBase interface

	UFUNCTION(BlueprintCallable, Category=LoadingScreen)
	FString GetDebugReasonForShowingOrHidingLoadingScreen() const
	{
		return DebugReasonForShowingOrHidingLoadingScreen;
	}

	/** Returns True when the loading screen is currently being shown */
	bool GetLoadingScreenDisplayStatus() const
	{
		return bCurrentlyShowingLoadingScreen;
	}

	/** Called when the loading screen visibility changes  */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadingScreenVisibilityChangedDelegate, bool);
	FORCEINLINE FOnLoadingScreenVisibilityChangedDelegate& OnLoadingScreenVisibilityChangedDelegate() { return LoadingScreenVisibilityChanged; }

	void RegisterLoadingProcessor(TScriptInterface<ILoadingProcessInterface> Interface);
	void UnregisterLoadingProcessor(TScriptInterface<ILoadingProcessInterface> Interface);
	
private:
	void HandlePreLoadMap(const FWorldContext& WorldContext, const FString& MapName);
	void HandlePostLoadMap(UWorld* World);

	/** 更新加载屏幕 */
	void UpdateLoadingScreen();

	/** 检查是否需要加载屏幕 */
	bool CheckForAnyNeedToShowLoadingScreen();

	/** Returns true if we want to be showing the loading screen (if we need to or are artificially forcing it on for other reasons).
	 * 如果我们想显示加载屏幕（如果我们需要或出于其他原因人为地将其打开），则返回true
	 */
	bool ShouldShowLoadingScreen();

	/** Returns true if we are in the initial loading flow before this screen should be used
	 * 如果我们在使用此屏幕之前处于初始加载流中，则返回true
	 */
	bool IsShowingInitialLoadingScreen() const;

	/** Shows the loading screen. Sets up the loading screen widget on the viewport */
	void ShowLoadingScreen();

	/** Hides the loading screen. The loading screen widget will be destroyed */
	void HideLoadingScreen();

	/** Removes the widget from the viewport */
	void RemoveWidgetFromViewport();

	/** Prevents input from being used in-game while the loading screen is visible */
	void StartBlockingInput();

	/** Resumes in-game input, if blocking */
	void StopBlockingInput();

	void ChangePerformanceSettings(bool bEnabingLoadingScreen);

public:

	// 开始加载地图
	UPROPERTY(BlueprintAssignable, Category = LoadingScreen)
	FOnPreLoadMapTriggered OnPreLoadMapTriggered;

	// 结束加载地图
	UPROPERTY(BlueprintAssignable, Category = LoadingScreen)
	FOnPostLoadMapTriggered OnPostLoadMapTriggered;
	
private:
	/** Delegate broadcast when the loading screen visibility changes */
	FOnLoadingScreenVisibilityChangedDelegate LoadingScreenVisibilityChanged;

	/** A reference to the loading screen widget we are displaying (if any) */
	TSharedPtr<SWidget> LoadingScreenWidget;

	/** Input processor to eat all input while the loading screen is shown */
	TSharedPtr<IInputProcessor> InputPreProcessor;

	/** External loading processors, components maybe actors that delay the loading. */
	TArray<TWeakInterfacePtr<ILoadingProcessInterface>> ExternalLoadingProcessors;

	/** The reason why the loading screen is up (or not) */
	FString DebugReasonForShowingOrHidingLoadingScreen;

	/** The time when we started showing the loading screen */
	double TimeLoadingScreenShown = 0.0;

	/** The time the loading screen most recently wanted to be dismissed (might still be up due to a min display duration requirement)
	 * 加载屏幕最近想要被关闭的时间（由于最小显示持续时间要求，可能仍在运行）
	 */
	double TimeLoadingScreenLastDismissed = -1.0;

	/** The time until the next log for why the loading screen is still up
	 * 直到下一个日志显示加载屏幕仍处于打开状态的时间
	 */
	double TimeUntilNextLogHeartbeatSeconds = 0.0;

	/** True when we are between PreLoadMap and PostLoadMap
	 * 当我们处于PreLoadMap和PostLoadMap之间时为True
	 */
	bool bCurrentlyInLoadMap = false;

	/** 第一次加载游戏，走moviePlayer */
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 LoadGameMapCount = 0;

	/** True when the loading screen is currently being shown
	 * 当前显示加载屏幕时为True
	 */
	bool bCurrentlyShowingLoadingScreen = false;
};
