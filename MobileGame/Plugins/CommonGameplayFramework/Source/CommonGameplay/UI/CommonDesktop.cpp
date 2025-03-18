// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonDesktop.h"

#include "CommonGameplay/System/CommonLogChannels.h"
#include "Components/CanvasPanel.h"

UCommonWindow* UCommonDesktop::ShowWindowByClass(TSubclassOf<UCommonWindow> WindowClass)
{
	if (WindowClass == nullptr)
	{
		UE_LOG(LogCommon, Warning, TEXT("UCommonDesktop::ShowWindowByClass WindowClass is nullptr"))
		return nullptr;
	}

	UCommonWindow* TempWind = FindWindowByClass(WindowClass);

	if (!TempWind)
	{
		// 如果不存在则创建
		TempWind = Cast<UCommonWindow>(CreateWidget(GetWorld(), WindowClass));
		TempWind->ParentDesktop = this;
		ChildWindows.AddUnique(TempWind);
		CanvasPanel->AddChildToCanvas(TempWind);
		TempWind->NativeOnShow();
	}

	// 把窗口显示在其他窗口最上层


	if (TempWind == TopActiveWindow)
	{
		// 存在且在Top(就是最顶层的)
		TempWind->NativeOnActivated();
		return TempWind;
	}
	else
	{
		// 顶层不是要显示的窗口
		if (TopActiveWindow)
		{
			// 存在但不是Top
			TopActiveWindow->NativeOnDeactivated();
			TempWind->NativeOnActivated();
			TopActiveWindow = TempWind;
			return TempWind;
		}
		else
		{
			// 顶层为空，那直接去当Top
			TempWind->NativeOnActivated();
			TopActiveWindow = TempWind;
			return TempWind;
		}
	}
}

void UCommonDesktop::HideWindowByClass(TSubclassOf<UCommonWindow> WindowClass)
{
	if (WindowClass == nullptr)
	{
		UE_LOG(LogCommon, Warning, TEXT("UCommonDesktop::HideWindowByClass WindowClass is nullptr"))
		return;
	}

	UCommonWindow* TempWind = FindWindowByClass(WindowClass);
	if (TempWind)
	{
		if (TempWind == TopActiveWindow)
		{
			TopActiveWindow = nullptr;
		}

		// 如果不是顶层，则先隐藏再删除
		TempWind->NativeOnHide();

		if (TempWind->bHideDestroy)
		{
			TempWind->RemoveFromParent();
			ChildWindows.Remove(TempWind);
		}else
		{
			TempWind->SetVisibility(ESlateVisibility::Collapsed);
		}

	}
}

UCommonWindow* UCommonDesktop::FindWindowByClass(TSubclassOf<UCommonWindow> WindowClass)
{
	for (TObjectPtr<UCommonWindow> window : ChildWindows)
	{
		if (window.GetClass() == WindowClass)
		{
			return window;
		}
	}
	return nullptr;
}
