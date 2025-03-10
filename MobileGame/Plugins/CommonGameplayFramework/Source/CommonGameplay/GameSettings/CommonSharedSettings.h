// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "GameFramework/SaveGame.h"
#include "CommonSharedSettings.generated.h"

/*
 * UCommonSharedSettings-“共享”设置作为USaveGame系统的一部分存储，这些设置不像本地设置那样是特定于<机器>的，可以安全地存储在云中并“共享”它们。
 * 使用保存游戏系统，我们还可以存储每个玩家的设置，所以控制器键绑定偏好等应该放在这里，因为如果这些存储在本地设置中，所有用户都会得到它们。
 */
UCLASS()
class COMMONGAMEPLAY_API UCommonSharedSettings : public ULocalPlayerSaveGame
{
	GENERATED_BODY()

public:
	UCommonSharedSettings();

	bool IsDirty() const { return bIsDirty; }
	void ClearDirtyFlag() { bIsDirty = false; }

	/** Synchronously loads a settings object, this is not valid to call before login
	* 同步加载设置对象，登录前调用此对象无效
	*/
	static UCommonSharedSettings* LoadOrCreateSettings(const UCommonLocalPlayer* LocalPlayer);

	/** Creates a temporary settings object, this will be replaced by one loaded from the user's save game
	* 创建一个临时设置对象，该对象将被从用户的保存游戏中加载的对象所替换
	*/
	static UCommonSharedSettings* CreateTemporarySettings(const UCommonLocalPlayer* LocalPlayer);

	/** 
	 * 将设置保存到磁盘
	 */
	virtual void SaveSettings();

	/** 
	 * 将设置应用于当前玩家
	 */
	virtual void ApplySettings();

private:
	bool bIsDirty = false;

public:
#pragma region 语言设置

	/** Gets the pending culture */
	const FString& GetPendingCulture() const;

	/** Sets the pending culture to apply */
	void SetPendingCulture(const FString& NewCulture);

	// Called when the culture changes.
	void OnCultureChanged();

	/** Clears the pending culture to apply */
	void ClearPendingCulture();

	bool IsUsingDefaultCulture() const;

	void ResetToDefaultCulture();
	bool ShouldResetToDefaultCulture() const { return bResetToDefaultCulture; }

	void ApplyCultureSettings();
	void ResetCultureToCurrentSettings();

private:
	/** The pending culture to apply */
	UPROPERTY(Transient)
	FString PendingCulture;

	/* If true, resets the culture to default. */
	bool bResetToDefaultCulture = false;

#pragma endregion
};
