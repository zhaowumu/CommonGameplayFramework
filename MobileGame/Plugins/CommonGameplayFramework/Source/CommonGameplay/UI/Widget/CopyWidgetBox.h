// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CopyWidgetBox.generated.h"

class UVerticalBox;
class UBorder;
/**
 * 
 */
UCLASS()
class COMMONGAMEPLAY_API UCopyWidgetBox : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBoxWidget;

	UFUNCTION(BlueprintCallable)
	void AddChildWidgetToSlate(UWidget* ChildWidget);

private:
	TSharedPtr<SVerticalBox> VerticalBoxContainer; // 用于存放多个 SWidget
};
