// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting.h"

UWorld* UGameSetting::GetWorld() const
{
	return LocalPlayer ? LocalPlayer->GetWorld() : nullptr;
}

void UGameSetting::SetDefaultValue(FGameSettingValue Value)
{
	DefaultSettingValue = Value;
}

void UGameSetting::SetDefaultValue_Bool(bool Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::BoolValue;
	DefaultSettingValue.BoolValue = Value;
}

void UGameSetting::SetDefaultValue_Float(float Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::FloatValue;
	DefaultSettingValue.FloatValue = Value;
}

void UGameSetting::SetDefaultValue_Int(int Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::IntValue;
	DefaultSettingValue.IntValue = Value;
}

void UGameSetting::SetDefaultValue_Enum(int Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::EnumValue;
	DefaultSettingValue.EnumValue = Value;
}

void UGameSetting::SetDefaultValue_String(FString Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::StringValue;
	DefaultSettingValue.StringValue = Value;
}

void UGameSetting::SetDefaultValue_Key(FKey Value)
{
	DefaultSettingValue.SettingValueType = EGameSettingValueType::KeyValue;
	DefaultSettingValue.KeyValue = Value;
}

void UGameSetting::AddDependencyParentSetting(UGameSetting* DependencyParentSetting)
{
	if (ensure(DependencyParentSetting))
	{
		//DependencyParentSetting->OnSettingChangedEvent.AddUObject(this, &ThisClass::HandleDependencySettingChanged);

		DependencyParentSetting->OnDependencyParentSettingChangedEvent.AddUObject(
			this, &ThisClass::HandleDependencyParentSettingChanged);
	}
}

void UGameSetting::HandleDependencySettingChanged(UGameSetting* DependencySetting, EGameSettingChangeReason Reason)
{
}

void UGameSetting::HandleDependencyParentSettingChanged(UGameSetting* DependencyParentSetting)
{
	// 依赖父项设置改变，重新设置可编辑
	if (DependencyParentSetting == ParentSetting)
	{
		RefreshEditableState();
	}
}

void UGameSetting::RefreshEditableState()
{
	
}


void UGameSetting::NotifySettingChanged(EGameSettingChangeReason Reason)
{
}

void UGameSetting::OnSettingChanged(EGameSettingChangeReason Reason)
{
}

void UGameSetting::NotifyEditConditionsChanged()
{
}

void UGameSetting::OnEditConditionsChanged()
{
}


void UGameSetting::Initialize(ULocalPlayer* InLocalPlayer)
{
}

void UGameSetting::Apply()
{
}
