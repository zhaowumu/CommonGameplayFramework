// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonWindow.h"
#include "CommonDesktop.generated.h"

class UCanvasPanel;
/**
 * 通用桌面UI（全屏）
 */
UCLASS(Abstract)
class COMMONGAMEPLAY_API UCommonDesktop : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CanvasPanel;

	UCommonWindow* ShowWindowByClass(TSubclassOf<UCommonWindow> WindowClass);

	void HideWindowByClass(TSubclassOf<UCommonWindow> WindowClass);

	UCommonWindow* FindWindowByClass(TSubclassOf<UCommonWindow> WindowClass);


private:

	UPROPERTY()
	TArray<TObjectPtr<UCommonWindow>> ChildWindows;

	UPROPERTY()
	TObjectPtr<UCommonWindow> TopActiveWindow;
	
};

