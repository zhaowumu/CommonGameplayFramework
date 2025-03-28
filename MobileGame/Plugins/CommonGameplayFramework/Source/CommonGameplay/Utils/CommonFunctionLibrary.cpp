// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFunctionLibrary.h"

#include "GeneralProjectSettings.h"
#include "CommonGameplay/System/CommonGameInstance.h"
#include "Kismet/GameplayStatics.h"

UCommonGameInstance* UCommonFunctionLibrary::GetCommonGameInstance(const UObject* WorldContextObject)
{
	if (auto GI = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		return Cast<UCommonGameInstance>(GI);
	}
	return nullptr;
}

FString UCommonFunctionLibrary::GetProjectVersion()
{
	// Get project settings.
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.ProjectVersion;
}

void UCommonFunctionLibrary::RestartGame()
{
#if !WITH_EDITOR
	
	FString CurrentExePath = FPlatformProcess::ExecutablePath(); // 获取当前可执行文件路径
	FString CommandLineArgs = FCommandLine::Get(); // 获取当前命令行参数（可选）

	// 创建新的进程并退出当前进程
	FPlatformProcess::CreateProc(*CurrentExePath, *CommandLineArgs, true, false, false, nullptr, 0, nullptr, nullptr);
	FGenericPlatformMisc::RequestExit(false);
#endif
}
