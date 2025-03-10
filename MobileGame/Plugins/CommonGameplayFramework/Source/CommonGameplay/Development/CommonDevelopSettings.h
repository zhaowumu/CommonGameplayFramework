// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameplay/GameSettings/GameSetting.h"
#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "CommonDevelopSettings.generated.h"



class UGameUIPolicy;
/**
 * 
 */
UCLASS(config=CommonGameplayFramework, defaultconfig, meta=(DisplayName="CommonGameplayFramework"))
class COMMONGAMEPLAY_API UCommonDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override
	{
		return FName("Game");
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="GetCommonDeveloperSettings"))
	static const UCommonDeveloperSettings* Get()
	{
		const UCommonDeveloperSettings* Settings = GetDefault<UCommonDeveloperSettings>();
		return Settings;
	}

public:
	// 默认使用使用MoviePlayer
	UPROPERTY(config, EditAnywhere, Category=LoadingScreen, meta=(MetaClass="/Script/UMG.UserWidget"))
	FSoftClassPath LoadingScreenWidget;

	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<UGameUIPolicy> UIPolicyClass;

	UPROPERTY(config, EditAnywhere, Category = GameSettings)
	TSoftObjectPtr<UDataTable> GameSettingDataTable;

	UFUNCTION(BlueprintPure, Category=GameSettings)
	static TArray<FCommonSettingCfgData> GetAllGameSettingDataList();


#pragma region 音频设置

#pragma endregion
};
