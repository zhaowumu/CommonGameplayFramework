// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "CommonInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FCommonInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Fei.Input"))
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const class UInputAction* InputAction = nullptr;
};

/**
 * Non-mutable data asset that contains input configuration properties.
 */
UCLASS(BlueprintType, Const)
class COMMONGAMEPLAY_API UCommonInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Fei")
	const UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "Fei")
	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InTag, bool bLogNotFound = false) const;

	// 所有者使用的输入操作列表。这些输入动作被映射到一个gameplay标签，必须手动绑定。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FCommonInputAction> NativeInputActions;

	//所有者使用的输入操作列表。这些输入动作被映射到一个游戏标签，并自动绑定到具有匹配输入标签的能力。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCommonInputAction> AbilityInputActions;
};
