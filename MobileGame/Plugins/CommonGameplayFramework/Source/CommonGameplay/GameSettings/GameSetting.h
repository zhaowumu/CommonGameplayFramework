// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "UObject/Object.h"
#include "Engine/LocalPlayer.h"
#include "GameSetting.generated.h"


class UGameSetting;
class UGameSettingCondition;
class UCommonSettingData;

/** Why did the setting change? */
UENUM(BlueprintType)
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
	None,
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EGameSettingValueType SettingValueType = EGameSettingValueType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::BoolValue"))
	bool BoolValue = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::FloatValue"))
	float FloatValue = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::IntValue"))
	int32 IntValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::StringValue"))
	FString StringValue = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::KeyValue"))
	FKey KeyValue = FKey();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::EnumValue"))
	TArray<FText> EnumArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		meta = (EditCondition = "SettingValueType == EGameSettingValueType::EnumValue"))
	uint8 EnumValue = 0;
};

/*
 * 设置配置表
 */
USTRUCT(BlueprintType)
struct FCommonTestStructure
{
	GENERATED_BODY()

public:
	// 效果名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName DevName = FName();
	// 显示名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName = FText::GetEmpty();
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName DevName = FName();
	// 显示名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText DisplayName = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameSettingValue DefaultValue;

	// 效果名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ConditionKey = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameSetting> SettingClass = nullptr;
};


/**
 * 单个游戏设置
 * 主要功能
 * 1.提供通用接口 用于获取和修改游戏设置的各种属性，如名称、描述、可见性等。
 * 2.支持可编辑状态 控制设置是否可以修改，并提供 EditCondition 机制来动态决定可编辑状态。
 * 3.支持事件回调 允许外部监听设置的更改，并在必要时做出响应。
 * 4.支持搜索与分析 提供可搜索文本及分析数据上报功能。
 */
UCLASS(BlueprintType, Abstract, Blueprintable)
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

	//DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSettingChanged, EGameSettingChangeReason, ChangeReason);

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
	UFUNCTION(BlueprintPure)
	FName GetDevName() const { return DevName; }

	void SetDevName(const FName& Value) { DevName = Value; }

	UFUNCTION(BlueprintPure)
	FText GetDisplayName() const { return DisplayName; }

	void SetDisplayName(const FText& Value) { DisplayName = Value; }


	/*TSubclassOf<UGameSettingCondition> GetConditionClass() const { return DefaultConditionClass; }

	void SetConditionClass(const TSubclassOf<UGameSettingCondition> Value) { DefaultConditionClass = Value; }*/

	FName GetConditionKey() const { return ConditionKey; }

	void SetConditionKey(const FName Value) { ConditionKey = Value; }

	UFUNCTION(BlueprintPure)
	EGameSettingValueType GetValueType() const { return DefaultSettingValue.SettingValueType; }

	UFUNCTION(BlueprintCallable)
	void SetDefaultValue(FGameSettingValue Value);
	void SetDefaultValue_Bool(bool Value);
	void SetDefaultValue_Float(float Value);
	void SetDefaultValue_Int(int Value);
	void SetDefaultValue_Enum(int Value);
	void SetDefaultValue_String(FString Value);
	void SetDefaultValue_Key(FKey Value);


	UFUNCTION(BlueprintPure)
	FGameSettingValue GetCurrentValue() const;
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue(FGameSettingValue Value);
	UFUNCTION(BlueprintPure)
	bool GetCurrentValue_Bool();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_Bool(bool Value);
	UFUNCTION(BlueprintPure)
	float GetCurrentValue_Float();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_Float(float Value);
	UFUNCTION(BlueprintPure)
	int GetCurrentValue_Int();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_Int(int Value);
	UFUNCTION(BlueprintPure)
	int GetCurrentValue_Enum();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_Enum(int Value);
	UFUNCTION(BlueprintPure)
	FString GetCurrentValue_String();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_String(FString Value);
	UFUNCTION(BlueprintPure)
	FKey GetCurrentValue_Key();
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue_Key(FKey Value);


	void SetSettingData(UCommonSettingData* InOwningSettingData) { OwningSettingData = InOwningSettingData; }

	/*
	 * 添加依赖游戏父项设置，添加一个依赖父项（我依赖别人），如果该依赖父项GameSetting的值发生变化，将重新评估当前设置的可编辑状态。
	 * 典型的例子就是（修改了一个A配置，它有依赖配置B，一般B会根据A的情况设置为默认值，并灰显）
	 */
	void AddDependencyParentSetting(UGameSetting* DependencyParentSetting);

	/**
	 * 绑定回调，我依赖的设置项发生了改变，那我就要重新评估自己的可编辑状态
	 */
	void HandleDependencyParentSettingChanged(UGameSetting* DependencyParentSetting);

	//void HandleDependencySettingChanged(UGameSetting* DependencySetting, EGameSettingChangeReason Reason);

	/** Notify that the setting changed */
	void NotifySettingChanged(EGameSettingChangeReason Reason);


	UFUNCTION(BlueprintCallable)
	void Initialize(UCommonLocalPlayer* InLocalPlayer);

	UFUNCTION(BlueprintPure)
	UCommonLocalPlayer* GetOwningLocalPlayer() const { return LocalPlayer; }


	UFUNCTION(BlueprintImplementableEvent)
	void SetRealValue(FGameSettingValue value);

	UFUNCTION(BlueprintImplementableEvent)
	FGameSettingValue GetRealValue();

	UFUNCTION(BlueprintImplementableEvent)
	bool IfConditionMet();

	UFUNCTION(BlueprintImplementableEvent)
	void ThenConditionDo(bool bMet);

	/**
    * 刷新可编辑状态，如何不可编辑就要设置为默认值
    */
	virtual void RefreshEditableState();


	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCondition_Enable, bool, bEnable);

	FOnCondition_Enable OnCondition_EnableDelegate;

	UFUNCTION(BlueprintCallable)
	void SetSettingEnable(bool bEnable);

	/*
	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCondition_Show, bool, bShow);
	FOnCondition_Show OnCondition_ShowDelegate;

	UFUNCTION(BlueprintCallable)
	void SetSettingShow(bool bShow);*/

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCondition_ChangeValue, FGameSettingValue, NewValue);

	FOnCondition_ChangeValue OnCondition_ChangeValueDelegate;

	// 被动的因为条件改值
	UFUNCTION(BlueprintCallable)
	void SetSettingChangeValue(FGameSettingValue NewValue);

	UFUNCTION(BlueprintCallable)
	void BindAndInitialize(const FOnCondition_Enable& FuncEnable, const FOnCondition_ChangeValue& FuncChangeValue);

	void Apply();

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameSetting> ParentSetting;

private:
	UPROPERTY(Transient)
	TObjectPtr<UCommonLocalPlayer> LocalPlayer;

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

	// 条件
	FName ConditionKey;
	//TSubclassOf<UGameSettingCondition> DefaultConditionClass;


	// 当前值
	FGameSettingValue GameSettingValue;
	// 默认值
	FGameSettingValue DefaultSettingValue;
};
