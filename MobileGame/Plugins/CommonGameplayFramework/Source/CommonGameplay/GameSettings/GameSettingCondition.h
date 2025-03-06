// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSetting.h"
#include "UObject/Object.h"
#include "GameSettingCondition.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, Blueprintable,Abstract)
class COMMONGAMEPLAY_API UGameSettingCondition : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UGameSetting> SelfSetting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UGameSetting> ParentSetting;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool IfConditionMet() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ThenDo(bool bConditionMet) const;



	UFUNCTION(BlueprintCallable)
	void SetSettingShow(bool bShow);
};
