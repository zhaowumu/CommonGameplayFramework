// Fill out your copyright notice in the Description page of Project Settings.


#include "CopyWidgetBox.h"

#include "Components/Border.h"
#include "Components/VerticalBox.h"


void UCopyWidgetBox::AddChildWidgetToSlate(UWidget* ChildWidget)
{
	if (ChildWidget)
	{
		// **获取 SWidget**
		TSharedRef<SWidget> ChildSlateWidget = ChildWidget->TakeWidget();
		// **确保 SVerticalBox 存在**
		
		// **如果 VerticalBoxContainer 为空，就动态获取**
		if (!VerticalBoxContainer.IsValid() && VerticalBoxWidget)
		{
			VerticalBoxContainer = StaticCastSharedRef<SVerticalBox>(VerticalBoxWidget->TakeWidget());
		}
		
		if (VerticalBoxContainer.IsValid())
		{
			VerticalBoxContainer->AddSlot()
			.AutoHeight()
			[
				ChildSlateWidget
			];
		}
	}
}
