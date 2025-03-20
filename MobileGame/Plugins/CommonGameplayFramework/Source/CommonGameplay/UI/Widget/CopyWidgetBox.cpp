// Fill out your copyright notice in the Description page of Project Settings.


#include "CopyWidgetBox.h"

#include "Components/Border.h"
#include "Components/VerticalBox.h"


void UCopyWidgetBox::AddChildWidgetToSlate(UWidget* ChildWidget)
{
	if (ChildWidget)
	{
		// **克隆一个新的 UWidget**
		UWidget* ClonedWidget = DuplicateObject<UWidget>(ChildWidget, this);

		if (ClonedWidget)
		{
			// 获取新的 SWidget
			TSharedRef<SWidget> NewChildSlateWidget = ClonedWidget->TakeWidget();

			if (!VerticalBoxContainer.IsValid() && VerticalBoxWidget)
			{
				VerticalBoxContainer = StaticCastSharedRef<SVerticalBox>(VerticalBoxWidget->TakeWidget());
			}

			if (VerticalBoxContainer.IsValid())
			{
				VerticalBoxContainer->AddSlot()
				                    .AutoHeight()
				[
					NewChildSlateWidget
				];
			}
		}
	}
}
