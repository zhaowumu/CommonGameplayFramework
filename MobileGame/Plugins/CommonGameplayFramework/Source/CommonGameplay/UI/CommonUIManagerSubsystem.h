// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"

#include "CommonUIManagerSubsystem.generated.h"

/**
 * 通用UI子系统
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:
	UCommonUIManagerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	// 通过 定时器 每帧更新 UI 显示，保持 UI 和 HUD 状态同步。
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	// 定时器句柄
	FTSTicker::FDelegateHandle TickHandle;
};
