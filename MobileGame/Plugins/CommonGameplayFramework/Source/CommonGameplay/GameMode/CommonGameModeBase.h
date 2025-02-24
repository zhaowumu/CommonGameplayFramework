// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "CommonGameModeBase.generated.h"

/**
 * 通用游戏模式
 */
UCLASS(Config = Game)
class COMMONGAMEPLAY_API ACommonGameModeBase : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	ACommonGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma region AGameModeBaseInterface

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

#pragma endregion

protected:
	void HandleMatchAssignmentIfNotExpectingOne();
};
