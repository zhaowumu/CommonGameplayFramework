// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSettingData.h"

#include "GameSettingCondition.h"
#include "CommonGameplay/Development/CommonDevelopSettings.h"
#include "CommonGameplay/System/CommonLogChannels.h"


UCommonSettingData::UCommonSettingData()
{
}


void UCommonSettingData::Initialize(ULocalPlayer* InLocalPlayer)
{
	OwningLocalPlayer = InLocalPlayer;

	UE_LOG(LogCommon, Log, TEXT("UCommonSettingData::Initialize"))

	// 这里读表设置
	TArray<FCommonSettingCfgData> GameSettingDataList = UCommonDeveloperSettings::GetAllGameSettingDataList();

	// 先创建基本设置
	for (const FCommonSettingCfgData& GameSettingData : GameSettingDataList)
	{
		// TODO 这里可以放到 Initialize
		UGameSetting* Setting = NewObject<UGameSetting>();
		Setting->SetDevName(GameSettingData.DevName);
		Setting->SetDisplayName(GameSettingData.DisplayName);
		Setting->SetDefaultValue(GameSettingData.DefaultValue);
		Setting->SetConditionKey(GameSettingData.ConditionKey);
		Setting->SetConditionClass(GameSettingData.EditCondition);
		Settings.Add(Setting);
	}

	// 添加互相之间的依赖条件
	for (UGameSetting* Setting : Settings)
	{
		TSubclassOf<UGameSettingCondition> CurClass = Setting->GetConditionClass();

		UGameSetting* ParentSetting = FindGameSettingByKey(Setting->GetConditionKey());

		// 如果有条件那就绑定
		if (CurClass && ParentSetting)
		{
			UGameSettingCondition* NewCondition = NewObject<UGameSettingCondition>(this, CurClass);
			NewCondition->ParentSetting = ParentSetting;
			NewCondition->SelfSetting = Setting;
			Setting->Condition = NewCondition;
			Setting->AddDependencyParentSetting(ParentSetting);
		}
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
