﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSetting.h"
#include "UObject/Object.h"
#include "CommonSettingData.generated.h"

/**
 * 通用游戏设置数据，每个玩家一个
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonSettingData : public UObject
{
	GENERATED_BODY()

public:
	UCommonSettingData();

	void Initialize(UCommonLocalPlayer* InLocalPlayer);

	UFUNCTION(BlueprintCallable)
	void SaveAndApplyChanges();


	UFUNCTION(BlueprintPure)
	UGameSetting* FindGameSettingByKey(const FName& Key);
	


	UPROPERTY(Transient)
	TObjectPtr<UCommonLocalPlayer> OwningLocalPlayer;

	/** The settings owned by this collection. */
	UPROPERTY()
	TArray<TObjectPtr<UGameSetting>> Settings;
};
