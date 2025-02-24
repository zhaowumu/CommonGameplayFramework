// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonWorldSettings.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Misc/UObjectToken.h"

ACommonWorldSettings:: ACommonWorldSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR
void ACommonWorldSettings::CheckForErrors()
{
	Super::CheckForErrors();

	// 创建 MapCheck 日志对象
	FMessageLog MapCheck("MapCheck");

	for (TActorIterator<APlayerStart> PlayerStartIt(GetWorld()); PlayerStartIt; ++PlayerStartIt)
	{
		/*APlayerStart* PlayerStart = *PlayerStartIt;
		if (IsValid(PlayerStart) && PlayerStart->GetClass() == APlayerStart::StaticClass())
		{
			MapCheck.Warning()
				->AddToken(FUObjectToken::Create(PlayerStart))
				->AddToken(FTextToken::Create(FText::FromString("is a normal APlayerStart, replace with ALyraPlayerStart.")));
		}*/
	}

	//@TODO: Make sure the soft object path is something that can actually be turned into a primary asset ID (e.g., is not pointing to an experience in an unscanned directory)
}
#endif