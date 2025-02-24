// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "CommonPlayerState.generated.h"

/**
 * 通用玩家状态
 */
UCLASS(Config = Game)
class COMMONGAMEPLAY_API ACommonPlayerState : public AModularPlayerState
{
	GENERATED_BODY()

public:
	ACommonPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
