// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputConfig.h"
#include "EnhancedInputComponent.h"
#include "CommonInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMMONGAMEPLAY_API UCommonInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	// 单独绑定
	template <class UserClass, typename FuncType>
	void BindNativeAction(const UCommonInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
	                      UserClass* Object, FuncType Func, bool bLogIfNotFound);


	// 统一绑定
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UCommonInputConfig* InputConfig, UserClass* Object,
	                        PressedFuncType PressedFunc,
	                        PressedFuncType HeldFunc,
	                        ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);
};

template <class UserClass, typename FuncType>
void UCommonInputComponent::BindNativeAction(const UCommonInputConfig* InputConfig, const FGameplayTag& InputTag,
                                          ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func,
                                          bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionByTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UCommonInputComponent::BindAbilityActions(const UCommonInputConfig* InputConfig, UserClass* Object,
                                            PressedFuncType PressedFunc, PressedFuncType HeldFunc,
                                            ReleasedFuncType ReleasedFunc,
                                            TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FCommonInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc,
				                           Action.InputTag).GetHandle());
			}

			if (HeldFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc,
										   Action.InputTag).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc,
				                           Action.InputTag).GetHandle());
			}
		}
	}
}
