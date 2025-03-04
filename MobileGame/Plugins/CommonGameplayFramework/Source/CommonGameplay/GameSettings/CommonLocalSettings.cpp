// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonLocalSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SoundControlBusMix.h"
#include "SoundControlBus.h"
#include "AudioModulationStatics.h"
#include "CommonGameplay/Development/CommonDevelopSettings.h"


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

	// 检查控制总线和控制总线混音是否已经加载
	// 如果这是第一次从 UI 调用设置函数，则可能需要加载
	if (!bSoundControlBusMixLoaded)
	{
		// 如果未加载，则调用函数加载用户控制总线混音
		LoadUserControlBusMix();
	}

	// 确保控制总线混音已加载，否则会触发断言并输出错误消息
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// 在本地缓存的控制总线映射中查找名为 "Overall" 的控制总线
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Overall")))
	{
		// 如果找到控制总线
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			// 调用函数为该控制总线设置音量
			SetVolumeForControlBus(ControlBusPtr, OverallVolume);
		}
	}
}

float UCommonLocalSettings::GetMusicVolume() const
{
	return MusicVolume;
}

void UCommonLocalSettings::SetMusicVolume(float InVolume)
{
	MusicVolume = InVolume;
	
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}
	
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));
	
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Music")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, MusicVolume);
		}
	}
}

float UCommonLocalSettings::GetSoundFXVolume() const
{
	return SoundFXVolume;
}

void UCommonLocalSettings::SetSoundFXVolume(float InVolume)
{
	SoundFXVolume = InVolume;
	
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}
	
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));
	
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("SoundFX")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, SoundFXVolume);
		}
	}
}

float UCommonLocalSettings::GetDialogueVolume() const
{
	return DialogueVolume;
}

void UCommonLocalSettings::SetDialogueVolume(float InVolume)
{
	DialogueVolume = InVolume;
	
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}
	
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));
	
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Dialogue")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, DialogueVolume);
		}
	}
}

float UCommonLocalSettings::GetVoiceChatVolume() const
{
	return VoiceChatVolume;
}

void UCommonLocalSettings::SetVoiceChatVolume(float InVolume)
{
	VoiceChatVolume = InVolume;

	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}
	
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));
	
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("VoiceChat")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, VoiceChatVolume);
		}
	}
}

void UCommonLocalSettings::LoadUserControlBusMix()
{
	// 确保 GEngine 存在
    if (GEngine)
    {
        // 获取当前游戏世界（UWorld）
        if (const UWorld* World = GEngine->GetCurrentPlayWorld())
        {
            // 获取 Lyra 的音频设置
            if (const UCommonDeveloperSettings* CommonSettings = GetDefault<UCommonDeveloperSettings>())
            {
                // 定义多个控制总线变量
                USoundControlBus* OverallControlBus = nullptr;  // 总音量控制总线
                USoundControlBus* MusicControlBus = nullptr;    // 音乐音量控制总线
                USoundControlBus* SoundFXControlBus = nullptr;  // 音效音量控制总线
                USoundControlBus* DialogueControlBus = nullptr; // 对话音量控制总线
                USoundControlBus* VoiceChatControlBus = nullptr;// 语音聊天音量控制总线

                // 清空 ControlBusMap，准备存储新的音量控制总线
                ControlBusMap.Empty();

                // 加载“总体”音量控制总线
                if (UObject* ObjPath = CommonSettings->OverallVolumeControlBus.TryLoad())
                {
                    if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
                    {
                        OverallControlBus = SoundControlBus;
                        ControlBusMap.Add(TEXT("Overall"), OverallControlBus);
                    }
                    else
                    {
                        ensureMsgf(SoundControlBus, TEXT("Overall Control Bus reference missing from Lyra Audio Settings."));
                    }
                }

                // 加载“音乐”音量控制总线
                if (UObject* ObjPath = CommonSettings->MusicVolumeControlBus.TryLoad())
                {
                    if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
                    {
                        MusicControlBus = SoundControlBus;
                        ControlBusMap.Add(TEXT("Music"), MusicControlBus);
                    }
                    else
                    {
                        ensureMsgf(SoundControlBus, TEXT("Music Control Bus reference missing from Lyra Audio Settings."));
                    }
                }

                // 加载“音效”音量控制总线
                if (UObject* ObjPath = CommonSettings->SoundFXVolumeControlBus.TryLoad())
                {
                    if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
                    {
                        SoundFXControlBus = SoundControlBus;
                        ControlBusMap.Add(TEXT("SoundFX"), SoundFXControlBus);
                    }
                    else
                    {
                        ensureMsgf(SoundControlBus, TEXT("SoundFX Control Bus reference missing from Lyra Audio Settings."));
                    }
                }

                // 加载“对话”音量控制总线
                if (UObject* ObjPath = CommonSettings->DialogueVolumeControlBus.TryLoad())
                {
                    if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
                    {
                        DialogueControlBus = SoundControlBus;
                        ControlBusMap.Add(TEXT("Dialogue"), DialogueControlBus);
                    }
                    else
                    {
                        ensureMsgf(SoundControlBus, TEXT("Dialogue Control Bus reference missing from Lyra Audio Settings."));
                    }
                }

                // 加载“语音聊天”音量控制总线
                if (UObject* ObjPath = CommonSettings->VoiceChatVolumeControlBus.TryLoad())
                {
                    if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
                    {
                        VoiceChatControlBus = SoundControlBus;
                        ControlBusMap.Add(TEXT("VoiceChat"), VoiceChatControlBus);
                    }
                    else
                    {
                        ensureMsgf(SoundControlBus, TEXT("VoiceChat Control Bus reference missing from Lyra Audio Settings."));
                    }
                }

                // 2.加载用户自定义的音量混音配置（Control Bus Mix）
                if (UObject* ObjPath = CommonSettings->UserSettingsControlBusMix.TryLoad())
                {
                    if (USoundControlBusMix* SoundControlBusMix = Cast<USoundControlBusMix>(ObjPath))
                    {
                        ControlBusMix = SoundControlBusMix;

                        // 创建各个音量控制总线的混音阶段
                        const FSoundControlBusMixStage OverallControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, OverallControlBus, OverallVolume);
                        const FSoundControlBusMixStage MusicControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, MusicControlBus, MusicVolume);
                        const FSoundControlBusMixStage SoundFXControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, SoundFXControlBus, SoundFXVolume);
                        const FSoundControlBusMixStage DialogueControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, DialogueControlBus, DialogueVolume);
                        const FSoundControlBusMixStage VoiceChatControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, VoiceChatControlBus, VoiceChatVolume);

                        // 将所有混音阶段加入数组
                        TArray<FSoundControlBusMixStage> ControlBusMixStageArray;
                        ControlBusMixStageArray.Add(OverallControlBusMixStage);
                        ControlBusMixStageArray.Add(MusicControlBusMixStage);
                        ControlBusMixStageArray.Add(SoundFXControlBusMixStage);
                        ControlBusMixStageArray.Add(DialogueControlBusMixStage);
                        ControlBusMixStageArray.Add(VoiceChatControlBusMixStage);

                        // 更新混音设置
                        UAudioModulationStatics::UpdateMix(World, ControlBusMix, ControlBusMixStageArray);

                        // 标记音量混音已加载
                        bSoundControlBusMixLoaded = true;
                    }
                    else
                    {
                        ensureMsgf(SoundControlBusMix, TEXT("User Settings Control Bus Mix reference missing from Lyra Audio Settings."));
                    }
                }
            }
        }
    }
}

void UCommonLocalSettings::SetVolumeForControlBus(USoundControlBus* InSoundControlBus, float InVolume)
{
	// 检查音量控制总线和混音是否已经加载
	// 如果这是第一次调用设置音量的函数，可能需要先加载控制总线混音
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// 确保控制总线混音已成功加载
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));
	
	// 如果所有的控制总线已经正确加载，我们就可以更新音量参数
	// 使用 AudioModulationStatics API 来调整控制总线的音量，并将设置应用到用户的混音配置
	if (GEngine && InSoundControlBus && bSoundControlBusMixLoaded)
	{
		// 获取当前的游戏世界（用于音频上下文）
		if (const UWorld* AudioWorld = GEngine->GetCurrentPlayWorld())
		{
			// 确保 Control Bus Mix 存在
			ensureMsgf(ControlBusMix, TEXT("Control Bus Mix failed to load."));

			// 创建并设置音量控制总线混音参数
			FSoundControlBusMixStage UpdatedControlBusMixStage;
			UpdatedControlBusMixStage.Bus = InSoundControlBus;  // 目标控制总线
			UpdatedControlBusMixStage.Value.TargetValue = InVolume; // 设定的目标音量
			UpdatedControlBusMixStage.Value.AttackTime = 0.01f; // 音量上升的时间（秒）
			UpdatedControlBusMixStage.Value.ReleaseTime = 0.01f; // 音量下降的时间（秒）

			// 将音量混音阶段加入数组（UpdateMix 函数需要数组作为参数）
			TArray<FSoundControlBusMixStage> UpdatedMixStageArray;
			UpdatedMixStageArray.Add(UpdatedControlBusMixStage);

			// 更新控制总线混音配置，使新的音量生效
			UAudioModulationStatics::UpdateMix(AudioWorld, ControlBusMix, UpdatedMixStageArray);
		}
	}

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
