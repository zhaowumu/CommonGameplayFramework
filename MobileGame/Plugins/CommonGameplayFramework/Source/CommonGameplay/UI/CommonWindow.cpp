// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonWindow.h"

#include "CommonDesktop.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UCommonWindow::SetZOrder(int32 InZOrder)
{
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (slot)
	{
		slot->SetZOrder(InZOrder);
		slot->SetAutoSize(true);
	}
}

void UCommonWindow::SetPosition(FVector2D InPos)
{
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (slot)
	{
		slot->SetPosition(InPos);
	}
}

void UCommonWindow::OnCloseClicked()
{
	if (ParentDesktop)
	{
		ParentDesktop->HideWindowByClass(GetClass());
	}
}

void UCommonWindow::NativeOnShow()
{
	SetZOrder(200);
	OnShow();

	Button_Close->OnClicked.AddDynamic(this, &UCommonWindow::OnCloseClicked);
}

void UCommonWindow::NativeOnHide()
{
	SetZOrder(200);
	OnHide();
}

void UCommonWindow::NativeOnActivated()
{
	// 设置窗口的层级
	SetZOrder(300);

	// 设置窗口的
	SetPosition(DefaultPosition);

	OnActivated();
}

void UCommonWindow::NativeOnDeactivated()
{
	SetZOrder(200);
	OnDeactivated();
}
