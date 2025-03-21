// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonPreLoadScreen.h"
#include "MoviePlayer.h"
#include "Misc/App.h"
#include "Modules/ModuleManager.h"
#include "PreLoadScreenManager.h"

#define LOCTEXT_NAMESPACE "FCommonLoadingScreenModule"

// PreLoadScreen是在引擎启动的过程种显示的。
class FCommonStartupLoadingScreenModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	bool IsGameModule() const override;

private:
	void OnPreLoadScreenManagerCleanUp();

	TSharedPtr<FCommonCustomSplashScreen> CustomSplashScreen;
	TSharedPtr<FCommonEarlyStartupScreen> EarlyStartupScreen;
	TSharedPtr<FCommonEngineLoadingScreen> EngineLoadingScreen;
};


void FCommonStartupLoadingScreenModule::StartupModule()
{
	// No need to load these assets on dedicated servers.
	// Still want to load them in commandlets so cook catches them
	//无需在专用服务器上加载这些资产。
	//仍然想在commandlets中加载它们，以便cook捕获它们
	if (!IsRunningDedicatedServer())
	{
		// 创建并初始化预加载屏幕
		CustomSplashScreen = MakeShared<FCommonCustomSplashScreen>();
		CustomSplashScreen->Init();
		/*EarlyStartupScreen = MakeShared<FCommonEarlyStartupScreen>();
		EarlyStartupScreen->Init();
		EngineLoadingScreen = MakeShared<FCommonEngineLoadingScreen>();
		EngineLoadingScreen->Init();*/

		/*FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.bWaitForManualStop = false;
		LoadingScreen.bAllowEngineTick = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 2.0f;
		LoadingScreen.bAllowInEarlyStartup = true;
		LoadingScreen.WidgetLoadingScreen = SNew(SImage).ColorAndOpacity(FLinearColor::Red);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);*/

		// 如果当前不是在编辑器中运行，且应用程序可以渲染，并且预加载屏幕管理器存在
		if (!GIsEditor && FApp::CanEverRender() && FPreLoadScreenManager::Get())
		{
			// 注册预加载屏幕到预加载屏幕管理器
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(CustomSplashScreen);
			//FPreLoadScreenManager::Get()->RegisterPreLoadScreen(EarlyStartupScreen);
			//FPreLoadScreenManager::Get()->RegisterPreLoadScreen(EngineLoadingScreen);
			// 绑定预加载屏幕管理器清理时的回调函数
			FPreLoadScreenManager::Get()->OnPreLoadScreenManagerCleanUp.AddRaw(
				this, &FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp);
		}
	}
}

void FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PreLoadScreenManager Cleanup"));

	//Once the PreLoadScreenManager is cleaning up, we can get rid of all our resources too
	//PreLoadScreenManager清理完毕后，我们也可以删除所有资源
	CustomSplashScreen.Reset();
	// 调用模块关闭函数
	ShutdownModule();
}

void FCommonStartupLoadingScreenModule::ShutdownModule()
{
}

bool FCommonStartupLoadingScreenModule::IsGameModule() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCommonStartupLoadingScreenModule, CommonStartupLoadingScreen)
