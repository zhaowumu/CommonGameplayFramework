// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting.h"

#include "GameSettingCondition.h"

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

FGameSettingValue UGameSetting::GetCurrentValue() const
{
	return GameSettingValue;
}

void UGameSetting::SetCurrentValue(FGameSettingValue Value)
{
	GameSettingValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

bool UGameSetting::GetCurrentValue_Bool()
{
	return GameSettingValue.BoolValue;
}

void UGameSetting::SetCurrentValue_Bool(bool Value)
{
	GameSettingValue.BoolValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

float UGameSetting::GetCurrentValue_Float()
{
	return GameSettingValue.FloatValue;
}

void UGameSetting::SetCurrentValue_Float(float Value)
{
	GameSettingValue.FloatValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

int UGameSetting::GetCurrentValue_Int()
{
	return GameSettingValue.IntValue;
}

void UGameSetting::SetCurrentValue_Int(int Value)
{
	GameSettingValue.IntValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

int UGameSetting::GetCurrentValue_Enum()
{
	return GameSettingValue.EnumValue;
}


void UGameSetting::SetCurrentValue_Enum(int Value)
{
	GameSettingValue.EnumValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

FString UGameSetting::GetCurrentValue_String()
{
	return GameSettingValue.StringValue;
}

void UGameSetting::SetCurrentValue_String(FString Value)
{
	GameSettingValue.StringValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

FKey UGameSetting::GetCurrentValue_Key()
{
	return GameSettingValue.KeyValue;
}

void UGameSetting::SetCurrentValue_Key(FKey Value)
{
	GameSettingValue.KeyValue = Value;
	OnSettingChangedEvent.Broadcast(this, EGameSettingChangeReason::Change);
	OnDependencyParentSettingChangedEvent.Broadcast(this);
}

void UGameSetting::AddDependencyParentSetting(UGameSetting* DependencyParentSetting)
{
	if (ensure(DependencyParentSetting))
	{
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
	if (Condition && Condition->ParentSetting == DependencyParentSetting)
	{
		RefreshEditableState();
	}
}

void UGameSetting::RefreshEditableState()
{
	if (Condition)
	{
		bool bMet = Condition->IfConditionMet();

		Condition->ThenDo(bMet);
	}
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
