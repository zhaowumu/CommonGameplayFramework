// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "CommonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COMMONGAMEPLAYFRAMEWORK_API ACommonGameModeBase : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	ACommonGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
