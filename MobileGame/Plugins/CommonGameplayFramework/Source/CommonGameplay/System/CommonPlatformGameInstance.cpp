// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonPlatformGameInstance.h"


#include "CommonSessionSubsystem.h"
#include "CommonUISettings.h"
#include "CommonUserSubsystem.h"

#include "ICommonUIModule.h"
#include "CommonGameplay/UI/Messaging/CommonGameDialog.h"
#include "CommonGameplay/UI/Messaging/CommonMessagingSubsystem.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonPlatformGameInstance)

UCommonPlatformGameInstance::UCommonPlatformGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCommonPlatformGameInstance::HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message)
{
	ULocalPlayer* FirstPlayer = GetFirstGamePlayer();
	// Forward severe ones to the error dialog for the first player
	if (FirstPlayer && MessageType.MatchesTag(FCommonUserTags::SystemMessage_Error))
	{
		if (UCommonMessagingSubsystem* Messaging = FirstPlayer->GetSubsystem<UCommonMessagingSubsystem>())
		{
			Messaging->ShowError(UCommonGameDialogDescriptor::CreateConfirmationOk(Title, Message));
		}
	}
}
