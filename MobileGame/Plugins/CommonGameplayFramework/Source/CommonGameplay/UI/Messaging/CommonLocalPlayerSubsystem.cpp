// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonLocalPlayerSubsystem.h"
#include "CommonGameDialog.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "CommonGameplay/System/CommonGameplayTags.h"
#include "CommonGameplay/System/CommonLogChannels.h"
#include "CommonGameplay/UI/CommonGameUISubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "UObject/UObjectHash.h"

//#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonLocalPlayerSubsystem)

class FSubsystemCollectionBase;
class UClass;

void UCommonLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	//checkf(ConfirmationDialogClass,TEXT("ConfirmationDialogClass must be set in the subsystem's settings"));

	ConfirmationDialogClassPtr = ConfirmationDialogClass.LoadSynchronous();
	ErrorDialogClassPtr = ErrorDialogClass.LoadSynchronous();

	if (ConfirmationDialogClassPtr || ConfirmationDialogClassPtr)
	{
		UE_LOG(LogCommon, Error,
		       TEXT("ConfirmationDialogClass or ErrorDialogClass is not set in the subsystem's settings"));
	}
}

void UCommonLocalPlayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UCommonLocalPlayerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	UGameInstance* GameInstance = CastChecked<ULocalPlayer>(Outer)->GetGameInstance();
	if (GameInstance && !GameInstance->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UCommonLocalPlayerSubsystem::ShowConfirmation(UCommonGameDialogDescriptor* DialogDescriptor,
                                                   FCommonMessagingResultDelegate ResultCallback)
{
	if (UCommonLocalPlayer* LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
	{
		if (UPrimaryGameLayout* RootLayout = LocalPlayer->GetRootUILayout())
		{
			RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(CommonGameplayTags::Fei_UI_Layer_Modal,
			                                                      ConfirmationDialogClassPtr,
			                                                      [DialogDescriptor, ResultCallback](
			                                                      UCommonGameDialog& Dialog)
			                                                      {
				                                                      Dialog.SetupDialog(
					                                                      DialogDescriptor, ResultCallback);
			                                                      });
		}
	}
}

void UCommonLocalPlayerSubsystem::ShowError(UCommonGameDialogDescriptor* DialogDescriptor,
                                            FCommonMessagingResultDelegate ResultCallback)
{
	if (UCommonLocalPlayer* LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
	{
		if (UPrimaryGameLayout* RootLayout = LocalPlayer->GetRootUILayout())
		{
			RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(CommonGameplayTags::Fei_UI_Layer_Modal,
			                                                      ErrorDialogClassPtr,
			                                                      [DialogDescriptor, ResultCallback](
			                                                      UCommonGameDialog& Dialog)
			                                                      {
				                                                      Dialog.SetupDialog(
					                                                      DialogDescriptor, ResultCallback);
			                                                      });
		}
	}
}
