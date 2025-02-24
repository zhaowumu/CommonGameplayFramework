// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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


	
	// 默认使用使用MoviePlayer
	UPROPERTY(config, EditAnywhere, Category=LoadingScreen, meta=(MetaClass="/Script/UMG.UserWidget"))
	FSoftClassPath LoadingScreenWidget;
	

};
