// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonLocalSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SoundControlBusMix.h"
#include "SoundControlBus.h"
#include "AudioModulationStatics.h"


UCommonLocalSettings::UCommonLocalSettings()
{
}

UCommonLocalSettings* UCommonLocalSettings::Get()
{
	return GEngine ? CastChecked<UCommonLocalSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

void UCommonLocalSettings::SetToDefaults()
{
	Super::SetToDefaults();
}

void UCommonLocalSettings::LoadSettings(bool bForceReload)
{
	Super::LoadSettings(bForceReload);
}

void UCommonLocalSettings::ConfirmVideoMode()
{
	Super::ConfirmVideoMode();
}

float UCommonLocalSettings::GetEffectiveFrameRateLimit()
{
	return Super::GetEffectiveFrameRateLimit();
}

void UCommonLocalSettings::ResetToCurrentSettings()
{
	Super::ResetToCurrentSettings();
}

void UCommonLocalSettings::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();
}

int32 UCommonLocalSettings::GetOverallScalabilityLevel() const
{
	return Super::GetOverallScalabilityLevel();
}

void UCommonLocalSettings::SetOverallScalabilityLevel(int32 Value)
{
	Super::SetOverallScalabilityLevel(Value);
}

float UCommonLocalSettings::GetOverallVolume() const
{
	return OverallVolume;
}

void UCommonLocalSettings::SetOverallVolume(float InVolume)
{
	// 缓存传入的音量值
	OverallVolume = InVolume;
}

float UCommonLocalSettings::GetMusicVolume() const
{
	return MusicVolume;
}

void UCommonLocalSettings::SetMusicVolume(float InVolume)
{
	MusicVolume = InVolume;
}

float UCommonLocalSettings::GetSoundFXVolume() const
{
	return SoundFXVolume;
}

void UCommonLocalSettings::SetSoundFXVolume(float InVolume)
{
	SoundFXVolume = InVolume;
}

float UCommonLocalSettings::GetDialogueVolume() const
{
	return DialogueVolume;
}

void UCommonLocalSettings::SetDialogueVolume(float InVolume)
{
	DialogueVolume = InVolume;
}

float UCommonLocalSettings::GetVoiceChatVolume() const
{
	return VoiceChatVolume;
}

void UCommonLocalSettings::SetVoiceChatVolume(float InVolume)
{
	VoiceChatVolume = InVolume;
}

float UCommonLocalSettings::GetUIVolume() const
{
	return UIVolume;
}

void UCommonLocalSettings::SetUIVolume(float InVolume)
{
	UIVolume = InVolume;
}

float UCommonLocalSettings::GetDisplayGamma() const
{
	return DisplayGamma;
}

void UCommonLocalSettings::SetDisplayGamma(float InGamma)
{
	DisplayGamma = InGamma;
	ApplyDisplayGamma();
}

void UCommonLocalSettings::ApplyDisplayGamma()
{
	if (GEngine)
	{
		GEngine->DisplayGamma = DisplayGamma;
	}
}
