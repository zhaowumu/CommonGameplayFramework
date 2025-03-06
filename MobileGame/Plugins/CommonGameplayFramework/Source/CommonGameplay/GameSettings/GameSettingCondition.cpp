// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingCondition.h"


void UGameSettingCondition::SetSettingShow(bool bShow)
{
	if (ParentSetting)
	{
		ParentSetting->OnCondition_ShowDelegate.ExecuteIfBound(bShow);
	}
}
