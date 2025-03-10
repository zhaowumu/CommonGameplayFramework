// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSettingSubsystem.h"


UCommonSettingData* UCommonSettingSubsystem::GetLocalPlayerGameSettingData(ULocalPlayer* InLocalPlayer)
{
	if (!InLocalPlayer)
	{
		return nullptr;
	}

	// 先从缓存中找
	for (auto setting : LocalPlayerGameSettingDataList)
	{
		if (setting->OwningLocalPlayer == InLocalPlayer)
		{
			return setting;
		}
	}


	// 缓存中没有，创建一个
	UCommonSettingData* NewSettingData = NewObject<UCommonSettingData>(this);
	NewSettingData->Initialize(Cast<UCommonLocalPlayer>(InLocalPlayer));
	LocalPlayerGameSettingDataList.Add(NewSettingData);
	return NewSettingData;
}

TArray<UGameSetting*> UCommonSettingSubsystem::GetLocalPlayerGameSetting(ULocalPlayer* InLocalPlayer)
{
	return GetLocalPlayerGameSettingData(InLocalPlayer)->Settings;
}

void UCommonSettingSubsystem::SaveAndApplyGameSetting(ULocalPlayer* InLocalPlayer)
{
	GetLocalPlayerGameSettingData(InLocalPlayer)->SaveAndApplyChanges();
}
