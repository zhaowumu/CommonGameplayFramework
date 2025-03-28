// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonFunctionLibrary.generated.h"

class UCommonGameInstance;
/**
 * 
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject"))
	static UCommonGameInstance* GetCommonGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="Game")
	static FString GetProjectVersion();

	UFUNCTION(BlueprintCallable, Category="Game")
	static void RestartGame();
	
};
