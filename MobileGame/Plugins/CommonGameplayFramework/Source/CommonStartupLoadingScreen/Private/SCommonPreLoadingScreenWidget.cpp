// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCommonPreLoadingScreenWidget.h"

#include "Widgets/Layout/SBorder.h"

class FReferenceCollector;

#define LOCTEXT_NAMESPACE "SCommonPreLoadingScreenWidget"

void SCommonPreLoadingScreenWidget::Construct(const FArguments& InArgs)
{
	// 设置子控件为一个 SBorder，背景为黑色
	ChildSlot
	[
		SAssignNew(BorderWidget, SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		.BorderBackgroundColor(FLinearColor::White)
		.Padding(0)
	];
}

void SCommonPreLoadingScreenWidget::SetColor(FLinearColor InColor)
{
	if (BorderWidget.IsValid())
	{
		BorderWidget->SetBorderBackgroundColor(InColor);
	}
}

void SCommonPreLoadingScreenWidget::AddReferencedObjects(FReferenceCollector& Collector)
{
	//WidgetAssets.AddReferencedObjects(Collector);
}

FString SCommonPreLoadingScreenWidget::GetReferencerName() const
{
	return TEXT("SCommonPreLoadingScreenWidget");
}

#undef LOCTEXT_NAMESPACE
