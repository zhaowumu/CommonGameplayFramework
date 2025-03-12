// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonWindow.generated.h"

/**
 * 通用窗口，存在于Desktop中（非全屏）
 */
UCLASS(Abstract)
class COMMONGAMEPLAY_API UCommonWindow : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Title = FText();
};
