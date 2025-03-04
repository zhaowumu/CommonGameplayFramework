// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "CommonLocalSettings.generated.h"

class USoundControlBusMix;
class USoundControlBus;
/**
 * 针对于特定机器的设置（比如声音图像设置等）
 * 必须在Config\DefaultEngine.ini 中配置
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonLocalSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UCommonLocalSettings();

	static UCommonLocalSettings* Get();

	//~UGameUserSettings interface
	virtual void SetToDefaults() override;
	virtual void LoadSettings(bool bForceReload) override;
	virtual void ConfirmVideoMode() override;
	virtual float GetEffectiveFrameRateLimit() override;
	virtual void ResetToCurrentSettings() override;
	virtual void ApplyNonResolutionSettings() override;
	virtual int32 GetOverallScalabilityLevel() const override;
	virtual void SetOverallScalabilityLevel(int32 Value) override;
	//~End of UGameUserSettings interface


#pragma region Audio - Sound

public:

	UFUNCTION()
	float GetOverallVolume() const;
	UFUNCTION()
	void SetOverallVolume(float InVolume);

	UFUNCTION()
	float GetMusicVolume() const;
	UFUNCTION()
	void SetMusicVolume(float InVolume);

	UFUNCTION()
	float GetSoundFXVolume() const;
	UFUNCTION()
	void SetSoundFXVolume(float InVolume);

	UFUNCTION()
	float GetDialogueVolume() const;
	UFUNCTION()
	void SetDialogueVolume(float InVolume);

	UFUNCTION()
	float GetVoiceChatVolume() const;
	UFUNCTION()
	void SetVoiceChatVolume(float InVolume);

private:
	UPROPERTY(Config)
	float OverallVolume = 1.0f;
	UPROPERTY(Config)
	float MusicVolume = 1.0f;
	UPROPERTY(Config)
	float SoundFXVolume = 1.0f;
	UPROPERTY(Config)
	float DialogueVolume = 1.0f;
	UPROPERTY(Config)
	float VoiceChatVolume = 1.0f;

	UPROPERTY(Transient)
	TMap<FName/*SoundClassName*/, TObjectPtr<USoundControlBus>> ControlBusMap;
	
	UPROPERTY(Transient)
	TObjectPtr<USoundControlBusMix> ControlBusMix = nullptr;
	
	UPROPERTY(Transient)
	bool bSoundControlBusMixLoaded;
	
	void LoadUserControlBusMix();
	
	void SetVolumeForControlBus(USoundControlBus* InSoundControlBus, float InVolume);


#pragma endregion

#pragma region Brightness/Gamma

public:
	UFUNCTION()
	float GetDisplayGamma() const;
	UFUNCTION()
	void SetDisplayGamma(float InGamma);

private:
	void ApplyDisplayGamma();

	UPROPERTY(Config)
	float DisplayGamma = 2.2;

#pragma endregion
};

