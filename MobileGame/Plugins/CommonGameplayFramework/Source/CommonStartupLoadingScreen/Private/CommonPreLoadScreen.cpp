// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonPreLoadScreen.h"

#include "Misc/App.h"
#include "SCommonPreLoadingScreenWidget.h"

#define LOCTEXT_NAMESPACE "CommonPreLoadingScreen"

void FCommonCustomSplashScreen::Init()
{
	// Read from config here if needed.
	// EarlyStartupScreen - use GConfig to read raw values.
	// EngineLoadingScreen - UObjects like UDeveloperSettings may be used.
	
	// 创建并初始化预加载屏幕的 UI 控件
	EngineLoadingWidget = SNew(SImage).ColorAndOpacity(FLinearColor::Red);
	
	/*// 如果当前不是在编辑器中运行，且应用程序可以渲染
	if (!GIsEditor && FApp::CanEverRender())
	{
		// 创建并初始化预加载屏幕的 UI 控件
		EngineLoadingWidget = SNew(SCommonPreLoadingScreenWidget);

		// 设置颜色
		TSharedPtr<SCommonPreLoadingScreenWidget> LoadingScreenWidget = StaticCastSharedPtr<
			SCommonPreLoadingScreenWidget>(EngineLoadingWidget);
		if (LoadingScreenWidget.IsValid())
		{
			LoadingScreenWidget->SetColor(FLinearColor::Red); // 设置颜色为蓝色
		}
	}*/
}

void FCommonEarlyStartupScreen::Init()
{
	EngineLoadingWidget = SNew(SImage).ColorAndOpacity(FLinearColor::Yellow);
	// Read from config here if needed.
	// EarlyStartupScreen - use GConfig to read raw values.
	// EngineLoadingScreen - UObjects like UDeveloperSettings may be used.
	
	/*// 如果当前不是在编辑器中运行，且应用程序可以渲染
	if (!GIsEditor && FApp::CanEverRender())
	{
		// 创建并初始化预加载屏幕的 UI 控件
		EngineLoadingWidget = SNew(SCommonPreLoadingScreenWidget);



		// 设置颜色
		TSharedPtr<SCommonPreLoadingScreenWidget> LoadingScreenWidget = StaticCastSharedPtr<
			SCommonPreLoadingScreenWidget>(EngineLoadingWidget);
		if (LoadingScreenWidget.IsValid())
		{
			LoadingScreenWidget->SetColor(FLinearColor::Yellow); // 设置颜色为蓝色
		}
	}*/
}

void FCommonEngineLoadingScreen::Init()
{
	EngineLoadingWidget = SNew(SImage).ColorAndOpacity(FLinearColor::Blue);
	
	/*// 如果当前不是在编辑器中运行，且应用程序可以渲染
	if (!GIsEditor && FApp::CanEverRender())
	{
		// 创建并初始化预加载屏幕的 UI 控件
		EngineLoadingWidget = SNew(SCommonPreLoadingScreenWidget);

		// 设置颜色
		TSharedPtr<SCommonPreLoadingScreenWidget> LoadingScreenWidget = StaticCastSharedPtr<
			SCommonPreLoadingScreenWidget>(EngineLoadingWidget);
		if (LoadingScreenWidget.IsValid())
		{
			LoadingScreenWidget->SetColor(FLinearColor::Blue); // 设置颜色为蓝色
		}
	}*/
}

#undef LOCTEXT_NAMESPACE
