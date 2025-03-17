// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/Button.h"
#include "CommonWindow.generated.h"

class UCommonDesktop;
/**
 * 通用窗口，存在于Desktop中（非全屏）
 */
UCLASS(Abstract)
class COMMONGAMEPLAY_API UCommonWindow : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category=Window)
	TObjectPtr<UCommonDesktop> ParentDesktop;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Button_Close;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Title = FText();

	// 窗口默认位置(相对屏幕中心)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Window)
	FVector2D DefaultPosition = FVector2D(0);

	// 窗口位置
	UPROPERTY(BlueprintReadWrite, Category=Window)
	FVector2D LastDisplayPosition;

	// 窗口尺寸
	UPROPERTY(BlueprintReadWrite, Category=Window)
	FVector2D LastWindowSize;

	UFUNCTION(BlueprintCallable)
	void SetZOrder(int32 InZOrder);

	UFUNCTION(BlueprintCallable)
	void SetPosition(FVector2D InPos);

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = Window)
	void OnShow();
	virtual void NativeOnShow();

	UFUNCTION(BlueprintImplementableEvent, Category = Window)
	void OnHide();
	virtual void NativeOnHide();

	UFUNCTION(BlueprintImplementableEvent, Category = Window)
	void OnActivated();
	virtual void NativeOnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = Window)
	void OnDeactivated();
	virtual void NativeOnDeactivated();
};
