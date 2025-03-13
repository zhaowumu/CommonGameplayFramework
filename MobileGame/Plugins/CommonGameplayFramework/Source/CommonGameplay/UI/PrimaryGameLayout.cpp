// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrimaryGameLayout.h"

#include "Engine/GameInstance.h"
#include "GameUIManagerSubsystem.h"
#include "GameUIPolicy.h"
#include "Kismet/GameplayStatics.h"
#include "CommonGameplay/Player/CommonLocalPlayer.h"
#include "CommonGameplay/System/CommonLogChannels.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PrimaryGameLayout)

class UObject;

/*static*/
UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	APlayerController* PlayerController = GameInstance->GetPrimaryPlayerController(false);
	return GetPrimaryGameLayout(PlayerController);
}

/*static*/
UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayout(APlayerController* PlayerController)
{
	return PlayerController ? GetPrimaryGameLayout(Cast<UCommonLocalPlayer>(PlayerController->Player)) : nullptr;
}

/*static*/
UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayout(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
	{
		const UCommonLocalPlayer* CommonLocalPlayer = CastChecked<UCommonLocalPlayer>(LocalPlayer);
		if (const UGameInstance* GameInstance = CommonLocalPlayer->GetGameInstance())
		{
			if (UGameUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>())
			{
				if (const UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
				{
					if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CommonLocalPlayer))
					{
						return RootLayout;
					}
				}
			}
		}
	}

	return nullptr;
}

UPrimaryGameLayout::UPrimaryGameLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPrimaryGameLayout::SetIsDormant(bool InDormant)
{
	if (bIsDormant != InDormant)
	{
		const ULocalPlayer* LP = GetOwningLocalPlayer();
		const int32 PlayerId = LP ? LP->GetControllerId() : -1;
		const TCHAR* OldDormancyStr = bIsDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* NewDormancyStr = InDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* PrimaryPlayerStr = LP && LP->IsPrimaryPlayer() ? TEXT("[Primary]") : TEXT("[Non-Primary]");
		UE_LOG(LogCommon, Display, TEXT("%s PrimaryGameLayout Dormancy changed for [%d] from [%s] to [%s]"),
		       PrimaryPlayerStr, PlayerId, OldDormancyStr, NewDormancyStr);

		bIsDormant = InDormant;
		OnIsDormantChanged();
	}
}

void UPrimaryGameLayout::OnIsDormantChanged()
{
	//@TODO NDarnell Determine what to do with dormancy, in the past we treated dormancy as a way to shutoff rendering
	//and the view for the other local players when we force multiple players to use the player view of a single player.

	//if (UCommonLocalPlayer* LocalPlayer = GetOwningLocalPlayer<UCommonLocalPlayer>())
	//{
	//	// When the root layout is dormant, we don't want to render anything from the owner's view either
	//	LocalPlayer->SetIsPlayerViewEnabled(!bIsDormant);
	//}

	//SetVisibility(bIsDormant ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);

	//OnLayoutDormancyChanged().Broadcast(bIsDormant);
}

void UPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->OnTransitioningChanged.AddUObject(this, &UPrimaryGameLayout::OnWidgetStackTransitioning);
		// TODO: Consider allowing a transition duration, we currently set it to 0, because if it's not 0, the
		//       transition effect will cause focus to not transition properly to the new widgets when using
		//       gamepad always.
		// 考虑允许转换持续时间，我们目前将其设置为0，因为如果它不是0,当始终使用游戏手柄时，过渡效果会导致焦点无法正确过渡到新的小部件。

		LayerWidget->SetTransitionDuration(0.0);

		Layers.Add(LayerTag, LayerWidget);
	}
}

void UPrimaryGameLayout::OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget,
                                                    bool bIsTransitioning)
{
	if (bIsTransitioning)
	{
		const FName SuspendToken = UCommonUIExtensions::SuspendInputForPlayer(
			GetOwningLocalPlayer(), TEXT("GlobalStackTransion"));
		SuspendInputTokens.Add(SuspendToken);
	}
	else
	{
		if (ensure(SuspendInputTokens.Num() > 0))
		{
			const FName SuspendToken = SuspendInputTokens.Pop();
			UCommonUIExtensions::ResumeInputForPlayer(GetOwningLocalPlayer(), SuspendToken);
		}
	}
}

void UPrimaryGameLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is on so go searching.
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

TArray<UCommonActivatableWidget*> UPrimaryGameLayout::FindCommonActivatableWidgetByClass(
	TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	TArray<UCommonActivatableWidget*> OutWidgets;

	for (const TTuple<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>>& LayerKVP : Layers)
	{
		UCommonActivatableWidgetContainerBase* LayerContainer = LayerKVP.Value;

		const TArray<UCommonActivatableWidget*>& WidgetArray = LayerContainer->GetWidgetList();

		for (UCommonActivatableWidget* Widget : WidgetArray)
		{
			if (Widget->GetClass() == WidgetClass)
			{
				OutWidgets.Add(Widget);
			}
		}
	}

	return OutWidgets;
}

void UPrimaryGameLayout::RemoveCommonActivatableWidgetByClass(TSubclassOf<UCommonActivatableWidget> ActivatableWidget)
{
	if (!ActivatableWidget)
	{
		return;
	}

	const TArray<UCommonActivatableWidget*> Widgets = FindCommonActivatableWidgetByClass(ActivatableWidget);


	for (const TTuple<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>>& LayerKVP : Layers)
	{
		UCommonActivatableWidgetContainerBase* LayerContainer = LayerKVP.Value;

		const TArray<UCommonActivatableWidget*>& WidgetArray = LayerContainer->GetWidgetList();

		for (UCommonActivatableWidget* Widget : WidgetArray)
		{
			if (Widgets.Contains(Widget))
			{
				LayerContainer->RemoveWidget(*Widget);
			}
		}
	}
}

void UPrimaryGameLayout::RemoveDesktopWidget(TSubclassOf<UCommonDesktop> DesktopWidget)
{
	if (!DesktopWidget)
	{
		return;
	}

	const TArray<UCommonActivatableWidget*>& WidgetArray = Game_Stack->GetWidgetList();

	for (UCommonActivatableWidget* Widget : WidgetArray)
	{
		if (DesktopWidget == Widget->GetClass())
		{
			Game_Stack->RemoveWidget(*Widget);
		}
	}
}

void UPrimaryGameLayout::RemovePanelWidget(TSubclassOf<UCommonPanel> PanelWidget)
{
	if (!PanelWidget)
	{
		return;
	}

	const TArray<UCommonActivatableWidget*>& WidgetArray = Panel_Stack->GetWidgetList();

	for (UCommonActivatableWidget* Widget : WidgetArray)
	{
		if (PanelWidget == Widget->GetClass())
		{
			Panel_Stack->RemoveWidget(*Widget);
		}
	}
}

void UPrimaryGameLayout::PopPanelWidget() const
{
	if (UCommonActivatableWidget* curp = Panel_Stack->GetActiveWidget())
	{
		// TODO 或者直接detacitve?
		Panel_Stack->RemoveWidget(*curp);
	}
}

void UPrimaryGameLayout::AddPanelWithFunc(TSubclassOf<UCommonPanel> PanelWidget, FOnPanelWidgetAdded Func)
{
	if (PanelWidget)
	{
		TFunctionRef<void(UCommonActivatableWidget&)> InitInstanceFunc = [Func
			](UCommonActivatableWidget& WidgetInstance)
		{
			if (Func.IsBound())
			{
				Func.ExecuteIfBound(&WidgetInstance);
			}
		};

		Panel_Stack->AddWidget(PanelWidget, InitInstanceFunc);
	}
}

UCommonActivatableWidgetContainerBase* UPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName)
{
	return Layers.FindRef(LayerName);
}
