// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonLoadingScreenable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCommonLoadingScreenable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMMONLOADINGSCREEN_API ICommonLoadingScreenable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Loading Screen")
	void OnLoadingProcess(const int Process, const int Total, const FString& Reason);
};
