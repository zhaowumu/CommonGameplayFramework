// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSettingData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonSettingSubsystem.generated.h"

/**
 * 通用游戏设置子系统
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonSettingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	UCommonSettingData* GetLocalPlayerGameSettingData(ULocalPlayer* InLocalPlayer);


	UFUNCTION(BlueprintPure)
	TArray<UGameSetting*> GetLocalPlayerGameSetting(ULocalPlayer* InLocalPlayer);

	UFUNCTION(BlueprintCallable)
	void SaveAndApplyGameSetting(ULocalPlayer* InLocalPlayer);

private:

	UPROPERTY()
	TArray<TObjectPtr<UCommonSettingData>> LocalPlayerGameSettingDataList;
};

