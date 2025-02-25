// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/World.h"

#include "GameUIPolicy.generated.h"

class UCommonLocalPlayer;
class UGameUIManagerSubsystem;
class ULocalPlayer;
class UPrimaryGameLayout;

/**
 * 定义了本地多玩家交互
 */
UENUM()
enum class ELocalMultiplayerInteractionMode : uint8
{
	// Fullscreen viewport for the primary player only, regardless of the other player's existence
	// 仅主玩家拥有全屏视口，其他玩家不可见。
	PrimaryOnly,

	// Fullscreen viewport for one player, but players can swap control over who's is displayed and who's is dormant
	// 全屏视口供一个玩家使用，但玩家可以切换控制权，决定谁的视口显示，谁处于休眠状态。
	SingleToggle,

	// Viewports displayed simultaneously for both players
	// 所有玩家的视口同时显示，支持分屏模式。
	Simultaneous
};

/**
 * 根布局玩家视口布局相关的信息
 */
USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> RootLayout = nullptr;

	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UPrimaryGameLayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};

/*
 * UI界面策略
 */
UCLASS(Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class COMMONGAMEPLAY_API UGameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	template <typename GameUIPolicyClass = UGameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* WorldContextObject)
	{
		return Cast<GameUIPolicyClass>(GetGameUIPolicy(WorldContextObject));
	}

	static UGameUIPolicy* GetGameUIPolicy(const UObject* WorldContextObject);

public:
	virtual UWorld* GetWorld() const override;
	UGameUIManagerSubsystem* GetOwningUIManager() const;
	UPrimaryGameLayout* GetRootLayout(const UCommonLocalPlayer* LocalPlayer) const;

	// 获取当前的多玩家交互模式。
	ELocalMultiplayerInteractionMode GetLocalMultiplayerInteractionMode() const { return LocalMultiplayerInteractionMode; }

	// 请求主视口的控制权。
	void RequestPrimaryControl(UPrimaryGameLayout* Layout);

protected:
	// 在视口中添加或移除特定玩家的布局。
	void AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	void RemoveLayoutFromViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);

	// 布局事件回调
	virtual void OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	virtual void OnRootLayoutRemovedFromViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);
	virtual void OnRootLayoutReleased(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout);

	//为本地玩家创建布局Widget
	void CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer);
	// 返回要创建的布局小部件的类
	TSubclassOf<UPrimaryGameLayout> GetLayoutWidgetClass(UCommonLocalPlayer* LocalPlayer);

private:
	ELocalMultiplayerInteractionMode LocalMultiplayerInteractionMode = ELocalMultiplayerInteractionMode::PrimaryOnly;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;

	UPROPERTY(Transient)
	TArray<FRootViewportLayoutInfo> RootViewportLayouts;

private:
	// 玩家添加、移除、销毁事件回调通知
	void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	void NotifyPlayerRemoved(UCommonLocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer);

	friend class UGameUIManagerSubsystem;
};
