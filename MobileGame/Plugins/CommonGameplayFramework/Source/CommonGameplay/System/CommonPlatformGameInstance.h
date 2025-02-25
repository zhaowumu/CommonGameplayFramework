// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "CommonPlatformGameInstance.generated.h"

struct FGameplayTag;
/**
 * 通用移动平台GameInstance
 */
UCLASS(Abstract, Config = Game)
class COMMONGAMEPLAY_API UCommonPlatformGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()

public:
	UCommonPlatformGameInstance(const FObjectInitializer& ObjectInitializer);
	
	/** Handles errors/warnings from CommonUser, can be overridden per game */
	UFUNCTION()
	virtual void HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message);
};
