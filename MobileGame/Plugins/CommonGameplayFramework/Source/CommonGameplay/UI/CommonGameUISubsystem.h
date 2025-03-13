// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonDesktop.h"
#include "GameUIManagerSubsystem.h"
#include "CommonGameUISubsystem.generated.h"


/**
 * 通用UI子系统，
 * 拥有UIPolicy对象，
 * UIPolicy对象中又保存了每个本地玩家的UI布局
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonGameUISubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:
	UCommonGameUISubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	// 显示桌面，同时间只有一个桌面可以被显示激活，其他的最好销毁
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem,
		meta=(DeterminesOutputType="DesktopClass"))
	UCommonDesktop* ShowDesktopByClass(const ULocalPlayer* LocalPlayer,
	                                   TSubclassOf<UCommonDesktop> DesktopClass);

	// 隐藏桌面，同时间只有一个桌面可以被显示激活，其他的最好销毁，所以直接remove
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem)
	void HideDesktopByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonDesktop> DesktopClass);


	// 显示窗口，多个同时显示，调整层级为最上层
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem,
		meta=(DeterminesOutputType="WindowClass"))
	UCommonWindow* ShowWindowByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonWindow> WindowClass);

	// 隐藏窗口，多个同时显示，调整层级为下层
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem)
	void HideWindowByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonWindow> WindowClass);

	// 显示面板，用默认的Stack形式
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem,
		meta=(DeterminesOutputType="PanelClass"))
	UCommonPanel* ShowPanelByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonPanel> PanelClass);

	// 隐藏面板，用默认的Stack形式
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem)
	void HidePanelWithByClass(const ULocalPlayer* LocalPlayer, TSubclassOf<UCommonPanel> PanelClass);

	// 隐藏当前面板
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category=CommonUISubsystem)
	void PopPanel(const ULocalPlayer* LocalPlayer);





private:
	// 通过 定时器 每帧更新 UI 显示，保持 UI 和 HUD 状态同步。
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	// 定时器句柄
	FTSTicker::FDelegateHandle TickHandle;



};
