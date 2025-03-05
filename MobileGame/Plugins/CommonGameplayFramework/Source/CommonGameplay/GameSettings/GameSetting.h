// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/LocalPlayer.h"
#include "GameSetting.generated.h"


class UCommonSettingData;

/** Why did the setting change? */
enum class EGameSettingChangeReason : uint8
{
	Change,
	DependencyChanged,
	ResetToDefault,
	RestoreToInitial,
};

/** 游戏设置类型 */
UENUM(BlueprintType)
enum class EGameSettingValueType : uint8
{
	BoolValue,
	FloatValue,
	IntValue,
	EnumValue,
	StringValue,
	KeyValue
};

/**
 * 游戏设置值
 */
USTRUCT(BlueprintType)
struct FGameSettingValue
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGameSettingValueType SettingValueType = EGameSettingValueType::BoolValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::BoolValue"))
	bool BoolValue = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::FloatValue"))
	float FloatValue = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::IntValue"))
	int32 IntValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::StringValue"))
	FString StringValue = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::KeyValue"))
	FKey KeyValue = FKey();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::EnumValue"))
	uint8 EnumValue = 0;
};

/*
 * 设置配置表
 */
USTRUCT(BlueprintType)
struct FCommonSettingCfgData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 效果名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName DevName = FName();
	// 显示名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameSettingValue DefaultValue;
};


/**
 * 单个游戏设置
 * 主要功能
 * 1.提供通用接口 用于获取和修改游戏设置的各种属性，如名称、描述、可见性等。
 * 2.支持可编辑状态 控制设置是否可以修改，并提供 EditCondition 机制来动态决定可编辑状态。
 * 3.支持事件回调 允许外部监听设置的更改，并在必要时做出响应。
 * 4.支持搜索与分析 提供可搜索文本及分析数据上报功能。
 */
UCLASS(BlueprintType)
class COMMONGAMEPLAY_API UGameSetting : public UObject
{
	GENERATED_BODY()

public:
	UGameSetting()
	{
	}

	/** Gets the current world of the local player that owns these settings. */
	virtual UWorld* GetWorld() const override;

	DECLARE_EVENT_TwoParams(UGameSetting, FOnSettingChanged, UGameSetting* /*InSetting*/,
	                        EGameSettingChangeReason /*InChangeReason*/);

	DECLARE_EVENT_OneParam(UGameSetting, FOnSettingApplied, UGameSetting* /*InSetting*/);

	DECLARE_EVENT_OneParam(UGameSetting, FOnDependencyParentSettingChanged, UGameSetting* /*InSetting*/);

	// GameSetting修改
	FOnSettingChanged OnSettingChangedEvent;
	// GameSetting应用
	FOnSettingApplied OnSettingAppliedEvent;
	// GameSetting父项设置修改
	FOnDependencyParentSettingChanged OnDependencyParentSettingChangedEvent;

public:
	/**
	* 获取此设置的非本地化开发人员名称。这应该保持不变，并代表此设置数据中此设置的唯一标识符。
	*/
	UFUNCTION(BlueprintCallable)
	FName GetDevName() const { return DevName; }

	void SetDevName(const FName& Value) { DevName = Value; }

	UFUNCTION(BlueprintCallable)
	FText GetDisplayName() const { return DisplayName; }

	void SetDisplayName(const FText& Value) { DisplayName = Value; }

	void SetDefaultValue(FGameSettingValue Value);
	void SetDefaultValue_Bool(bool Value);
	void SetDefaultValue_Float(float Value);
	void SetDefaultValue_Int(int Value);
	void SetDefaultValue_Enum(int Value);
	void SetDefaultValue_String(FString Value);
	void SetDefaultValue_Key(FKey Value);

	void SetSettingData(UCommonSettingData* InOwningSettingData) { OwningSettingData = InOwningSettingData; }

	/*
	 * 添加依赖游戏父项设置，添加一个依赖父项（我依赖别人），如果该依赖父项GameSetting的值发生变化，将重新评估当前设置的可编辑状态。
	 * 典型的例子就是（修改了一个A配置，它有依赖配置B，一般B会根据A的情况设置为默认值，并灰显）
	 */
	void AddDependencyParentSetting(UGameSetting* DependencyParentSetting);

	/**
	 * 绑定回调，我依赖的设置项发生了改变，那我就要重新评估自己的可编辑状态
	 */
	void HandleDependencySettingChanged(UGameSetting* DependencySetting, EGameSettingChangeReason Reason);
	void HandleDependencyParentSettingChanged(UGameSetting* DependencyParentSetting);

	/** Notify that the setting changed */
	void NotifySettingChanged(EGameSettingChangeReason Reason);
	virtual void OnSettingChanged(EGameSettingChangeReason Reason);

	/** Notify that the settings edit conditions changed.  This may mean it's now invisible, or disabled, or possibly that the options have changed in some meaningful way. */
	void NotifyEditConditionsChanged();
	virtual void OnEditConditionsChanged();


	void Initialize(ULocalPlayer* InLocalPlayer);

	/**
    * 刷新可编辑状态，如何不可编辑就要设置为默认值
    */
	virtual void RefreshEditableState();

	void Apply();

private:
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer;

	UPROPERTY(Transient)
	TObjectPtr<UGameSetting> ParentSetting;

	UPROPERTY(Transient)
	TObjectPtr<UCommonSettingData> OwningSettingData;


	// 唯一标识名
	FName DevName;
	// 显示名称
	FText DisplayName;
	// 描述
	FText DescriptionRichText;
	// 警告
	FText WarningRichText;

	// 当前值
	FGameSettingValue GameSettingValue;
	// 默认值
	FGameSettingValue DefaultSettingValue;
};
