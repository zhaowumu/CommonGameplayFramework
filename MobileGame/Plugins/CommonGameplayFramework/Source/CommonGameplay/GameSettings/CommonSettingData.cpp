// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSettingData.h"

#include "CommonLocalSettings.h"
#include "CommonSharedSettings.h"
#include "CommonGameplay/Development/CommonDevelopSettings.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "CommonGameplay/System/CommonLogChannels.h"


UCommonSettingData::UCommonSettingData()
{
}


void UCommonSettingData::Initialize(UCommonLocalPlayer* InLocalPlayer)
{
	OwningLocalPlayer = InLocalPlayer;

	UE_LOG(LogCommon, Log, TEXT("UCommonSettingData::Initialize"))

	// 这里读表设置
	TArray<FCommonSettingCfgData> GameSettingDataList = UCommonDeveloperSettings::GetAllGameSettingDataList();

	// 先创建基本设置
	for (const FCommonSettingCfgData& GameSettingData : GameSettingDataList)
	{
		if (GameSettingData.SettingClass == nullptr)
		{
			continue;
		}
		// TODO 这里可以放到 蓝图中设置
		UGameSetting* Setting = NewObject<UGameSetting>(this, GameSettingData.SettingClass);


		Setting->SetDevName(GameSettingData.DevName);
		Setting->SetDisplayName(GameSettingData.DisplayName);
		Setting->SetDefaultValue(GameSettingData.DefaultValue);


		Setting->SetConditionKey(GameSettingData.ConditionKey);
		//Setting->SetConditionClass(GameSettingData.ConditionClass);

		Settings.Add(Setting);
	}

	// 添加互相之间的依赖条件
	for (UGameSetting* Setting : Settings)
	{
		//TSubclassOf<UGameSettingCondition> CurClass = Setting->GetConditionClass();
		UGameSetting* ParentS = FindGameSettingByKey(Setting->GetConditionKey());

		// 如果有条件那就绑定
		if (ParentS)
		{
			//UGameSettingCondition* NewCondition = NewObject<UGameSettingCondition>(this, CurClass);

			Setting->AddDependencyParentSetting(ParentS);
		}

		Setting->Initialize(OwningLocalPlayer);


	}
}

void UCommonSettingData::SaveAndApplyChanges()
{
	if (UCommonLocalPlayer* LocalCommonPlayer = Cast<UCommonLocalPlayer>(OwningLocalPlayer))
	{
		// Game user settings need to be applied to handle things like resolution, this saves indirectly
		LocalCommonPlayer->GetLocalSettings()->ApplySettings(false);

		LocalCommonPlayer->GetSharedSettings()->ApplySettings();
		LocalCommonPlayer->GetSharedSettings()->SaveSettings();
	}
}

UGameSetting* UCommonSettingData::FindGameSettingByKey(const FName& Key)
{
	for (UGameSetting* Setting : Settings)
	{
		if (Setting->GetDevName() == Key)
		{
			return Setting;
		}
	}
	return nullptr;
}
