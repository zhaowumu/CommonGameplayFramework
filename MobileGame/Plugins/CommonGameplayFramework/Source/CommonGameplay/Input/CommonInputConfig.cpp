// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonInputConfig.h"
#include "CommonGameplay/System/CommonLogChannels.h"

const UInputAction* UCommonInputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
	for (const FCommonInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogCommon, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."),
			   *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UCommonInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InTag, bool bLogNotFound) const
{
	for (const FCommonInputAction& action : AbilityInputActions)
	{
		if (action.InputAction && action.InputTag == InTag)
		{
			return action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogCommon, Error, TEXT("Can't find abilityInputAction by Input Tag (%s)"), *InTag.ToString())
	}
	return nullptr;
}
