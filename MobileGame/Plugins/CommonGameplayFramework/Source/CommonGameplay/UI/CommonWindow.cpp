// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonWindow.h"

#include "CommonDesktop.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "CommonGameplay/Development/CommonDevelopSettings.h"
#include "Components/CanvasPanelSlot.h"
#include "Widget/CopyWidgetBox.h"


void UCommonWindow::SetZOrder(int32 InZOrder)
{
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (slot)
	{
		slot->SetZOrder(InZOrder);
		slot->SetAutoSize(true);
	}
}

FVector2D UCommonWindow::GetPosition()
{
	FVector2D pos = FVector2D::ZeroVector;
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (slot)
	{
		pos = slot->GetPosition();
	}
	return pos;
}

/*void UCommonWindow::SetPosition(FVector2D InPos)
{
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (slot)
	{
		slot->SetPosition(InPos);
	}
}*/

void UCommonWindow::SafeSetPosition(FVector2D InPos)
{
	UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (!slot)
	{
		UE_LOG(LogTemp, Error, TEXT("UBaseWindow::SaveSetPosition 窗口: %s 没有有效的slot"), *this->GetName());
		return;
	}

	FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld()) /
		UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	FVector2D size = this->GetCachedGeometry().Size;

	FVector2D safeTargetPos = InPos;

	safeTargetPos.X = FMath::Clamp(safeTargetPos.X,
	                               size.X * WindowMargin.Left,
	                               viewportSize.X - (size.X * (WindowMargin.Right +
		                               1))
	);

	safeTargetPos.Y = FMath::Clamp(safeTargetPos.Y,
	                               size.Y * WindowMargin.Top,
	                               viewportSize.Y - (size.Y * (WindowMargin.Bottom
		                               + 1))
	);
	LastDisplayPosition = safeTargetPos;
	slot->SetPosition(safeTargetPos);
}


void UCommonWindow::NativeOnShow()
{
	SetZOrder(200);
	OnShow();
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	LastDisplayPosition = DefaultPosition;
	Button_Close->OnClicked.AddDynamic(this, &UCommonWindow::OnCloseClicked);
}

void UCommonWindow::NativeOnHide()
{
	SetZOrder(200);
	OnHide();
}

void UCommonWindow::OnCloseClicked()
{
	if (ParentDesktop)
	{
		ParentDesktop->HideWindowByClass(GetClass());
	}
}


void UCommonWindow::NativeOnActivated()
{
	// 设置窗口的层级
	SetZOrder(300);

	// 设置窗口的
	SafeSetPosition(LastDisplayPosition);

	OnActivated();
}

void UCommonWindow::NativeOnDeactivated()
{
	SetZOrder(200);
	OnDeactivated();
}


FReply UCommonWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// 检查是否点击了 Button_Title
		if (Image_Title)
		{
			// 获取 Button_Title 的几何信息                
			FGeometry ButtonGeometry = Image_Title->GetCachedGeometry();

			// 将鼠标点击的位置转换为 Button_Title 的局部坐标
			FVector2D LocalMousePosition = InMouseEvent.GetScreenSpacePosition();

			// 检查鼠标点击的位置是否在 Button_Title 的边界内
			if (ButtonGeometry.IsUnderLocation(LocalMousePosition))
			{
				// 点击了 Button_Title，开始拖动
				bIsDragging = true;
				// 左上角位置
				StartDragWindowPosition = GetPosition();

				// 鼠标位置
				StartDragMouseViewportPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

				// 置顶窗口
				if (ParentDesktop)
				{
					ParentDesktop->ShowWindowByClass(GetClass());
				}


				/*// 获取 FSlateUser
				int32 UserIndex = InMouseEvent.GetUserIndex(); // 从 FDragDropEvent 获取用户索引
				TSharedPtr<FSlateUser> SlateUser = FSlateApplication::Get().GetUser(UserIndex);

				if (SlateUser.IsValid())
				{
					// 将 DragDropContent 置空
					SlateUser->CancelDragDrop();
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
													 FString::Printf(TEXT("SlateUser: %d"), UserIndex));
				}*/

				
				/*
				FEventReply replay =UWidgetBlueprintLibrary::Handled();
				replay = UWidgetBlueprintLibrary::DetectDrag(replay, this, EKeys::LeftMouseButton);
				*/

				FEventReply replay = UWidgetBlueprintLibrary::DetectDragIfPressed(
					InMouseEvent, this, EKeys::LeftMouseButton);
				return replay.NativeReply;
			}
		}

		// 置顶窗口
		if (ParentDesktop)
		{
			ParentDesktop->ShowWindowByClass(GetClass());
		}
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCommonWindow::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                         UDragDropOperation*& OutOperation)
{
	if (bIsDragging)
	{
		UDragDropOperation* DDO = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 FString::Printf(TEXT("DDO: %s"), *DDO->GetName()));


		UCommonWindow* WidgetToDrag = DuplicateObject<UCommonWindow>(this, GetWorld());

		DDO->DefaultDragVisual = WidgetToDrag;
		DDO->Pivot = EDragPivot::MouseDown;
		DDO->Offset = FVector2D(0, 0);
		OutOperation = DDO;
		SetRenderOpacity(0.3f);
	}

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UCommonWindow::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	InOperation->DefaultDragVisual->RemoveFromParent();
	SetRenderOpacity(1.0f);
	FVector2D cur = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FVector2D targetPos = cur - StartDragMouseViewportPosition +
		StartDragWindowPosition;
	// 安全的设置位置不要超出边界
	SafeSetPosition(targetPos);

	bIsDragging = false;
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

FReply UCommonWindow::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	/*FEventReply EventReply;
	EventReply.NativeReply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	/* 如果蓝图没有处理,将由我们处理 #1#
	if (!EventReply.NativeReply.IsEventHandled())
	{
		EventReply.NativeReply = FReply::Handled();
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		EventReply.NativeReply.EndDragDrop().ReleaseMouseCapture();
	}
	return EventReply.NativeReply;*/

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}
