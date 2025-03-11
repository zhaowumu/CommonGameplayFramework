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
 * 在编辑器中保存在\YourGameName\Saved\Config\WindowsEditor\GameUserSettings.ini
 * 在Windows中保存在\YourGameName\Saved\Config\Windows\GameUserSettings.ini
 * Windows打包之后WindowsNoEditor\项目名\Saved\Config\WindowsNoEditor路径下的GameUserConfig.ini
 * Android:/storage/emulated/0/Android/data/<YourGamePackageName>/files/Saved/Config/Android/GameUserSettings.ini
 * IOS:<AppSandbox>/Documents/Saved/Config/IOS/GameUserSettings.ini
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonLocalSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UCommonLocalSettings();

	static UCommonLocalSettings* Get();

	// TODO 图像质量、帧率、移动平台等
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


#pragma region Audio

public:

	UFUNCTION(BlueprintPure)
	float GetOverallVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetOverallVolume(float InVolume);

	UFUNCTION(BlueprintPure)
	float GetMusicVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetMusicVolume(float InVolume);

	UFUNCTION(BlueprintPure)
	float GetSoundFXVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetSoundFXVolume(float InVolume);

	UFUNCTION(BlueprintPure)
	float GetDialogueVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetDialogueVolume(float InVolume);

	UFUNCTION(BlueprintPure)
	float GetVoiceChatVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetVoiceChatVolume(float InVolume);

	UFUNCTION(BlueprintPure)
	float GetUIVolume() const;
	UFUNCTION(BlueprintCallable)
	void SetUIVolume(float InVolume);

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
	UPROPERTY(Config)
	float UIVolume = 1.0f;

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



