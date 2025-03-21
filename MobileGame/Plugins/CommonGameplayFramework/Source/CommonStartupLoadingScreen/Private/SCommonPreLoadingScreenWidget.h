// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UObject/GCObject.h"
#include "Widgets/Accessibility/SlateWidgetAccessibleTypes.h"
#include "Widgets/SCompoundWidget.h"

class FReferenceCollector;

class SCommonPreLoadingScreenWidget : public SCompoundWidget, public FGCObject
{
public:
	// Slate 宏，定义 UI 控件的参数
	SLATE_BEGIN_ARGS(SCommonPreLoadingScreenWidget)
		{
		}

	SLATE_END_ARGS()

	// 构造函数，用于构建 UI 控件
	void Construct(const FArguments& InArgs);

	void SetColor(FLinearColor InColor);

	//~ Begin FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	//~ End FGCObject interface

private:
	TSharedPtr<SBorder> BorderWidget;
};
