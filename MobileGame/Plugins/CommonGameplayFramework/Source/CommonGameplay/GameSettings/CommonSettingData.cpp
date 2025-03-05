// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSettingData.h"

#include "CommonGameplay/Development/CommonDevelopSettings.h"


UCommonSettingData::UCommonSettingData()
{
}


void UCommonSettingData::Initialize(ULocalPlayer* InLocalPlayer)
{
	OwningLocalPlayer = InLocalPlayer;

	// 这里读表设置
	TArray<FCommonSettingCfgData> GameSettingDataList = UCommonDeveloperSettings::GetAllGameSettingDataList();

	for (const FCommonSettingCfgData& GameSettingData : GameSettingDataList)
	{
		UGameSetting* Setting = NewObject<UGameSetting>();
		Setting->SetDevName(GameSettingData.DevName);
		Setting->SetDisplayName(GameSettingData.DisplayName);
		Setting->SetDefaultValue(GameSettingData.DefaultValue);
		Settings.Add(Setting);
	}
}
