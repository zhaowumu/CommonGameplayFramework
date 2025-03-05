// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSettingSubsystem.h"

UCommonSettingData* UCommonSettingSubsystem::GetLocalPlayerGameSettingData(ULocalPlayer* InLocalPlayer)
{
	for (auto setting : LocalPlayerGameSettingDataList)
	{
		if (setting->OwningLocalPlayer == InLocalPlayer)
		{
			return setting;
		}
	}

	if (InLocalPlayer)
	{
		UCommonSettingData* NewSettingData = NewObject<UCommonSettingData>();
		NewSettingData->Initialize(InLocalPlayer);
		LocalPlayerGameSettingDataList.Add(NewSettingData);
		return NewSettingData;
	}
	
	return nullptr;
}
