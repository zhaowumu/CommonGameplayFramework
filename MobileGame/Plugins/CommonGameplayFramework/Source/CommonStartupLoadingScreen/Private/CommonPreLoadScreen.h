// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PreLoadScreenBase.h"

class SWidget;

/*
 *https://unrealist.org/engine-startup-preload-screens/
 *https://zhuanlan.zhihu.com/p/608502007
 *LoadingPhase和EPreLoadScreenTypes（粗体）的时序如下
其中三个时间点---
EarliestPossible->PostConfigInit->PostSplashScreen
->---CustomSplashScreen
->PreEarlyLoadingScreen
->---EarlyStartupScreen
->PreLoadingScreen
->---EngineLoadingScreen
->PreDefault->Default->PostDefault->PostEngineInit
如果把模块加载时间设置在PostSplashScreen阶段，
3个时间点就都可以选用了。loading screen依赖movie player和slate render，
二者在PostConfigInit和PostSplashScreen之间已经可以用了，也许也可以播出来，够勇的可以试试。
*/

class FCommonCustomSplashScreen : public FPreLoadScreenBase
{
public:
	
	/*** IPreLoadScreen Implementation ***/
	virtual void Init() override;
	// 显示时间点
	virtual EPreLoadScreenTypes GetPreLoadScreenType() const override { return EPreLoadScreenTypes::CustomSplashScreen; }
	virtual TSharedPtr<SWidget> GetWidget() override { return EngineLoadingWidget; }
private:
	// 预加载屏幕的 UI 控件共享指针
	TSharedPtr<SWidget> EngineLoadingWidget;
};


class FCommonEarlyStartupScreen : public FPreLoadScreenBase
{
public:
	
    /*** IPreLoadScreen Implementation ***/
	virtual void Init() override;
	// 显示时间点
    virtual EPreLoadScreenTypes GetPreLoadScreenType() const override { return EPreLoadScreenTypes::EarlyStartupScreen; }
    virtual TSharedPtr<SWidget> GetWidget() override { return EngineLoadingWidget; }
private:
	// 预加载屏幕的 UI 控件共享指针
    TSharedPtr<SWidget> EngineLoadingWidget;
};

class FCommonEngineLoadingScreen : public FPreLoadScreenBase
{
public:
	
	/*** IPreLoadScreen Implementation ***/
	virtual void Init() override;
	// 显示时间点
	virtual EPreLoadScreenTypes GetPreLoadScreenType() const override { return EPreLoadScreenTypes::EngineLoadingScreen; }
	virtual TSharedPtr<SWidget> GetWidget() override { return EngineLoadingWidget; }
private:
	// 预加载屏幕的 UI 控件共享指针
	TSharedPtr<SWidget> EngineLoadingWidget;
};