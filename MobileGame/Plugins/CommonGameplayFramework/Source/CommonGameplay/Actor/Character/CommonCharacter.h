// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "CommonCharacter.generated.h"

/**
 * 通用角色基类
 */
UCLASS()
class COMMONGAMEPLAY_API ACommonCharacter : public AModularCharacter
{
	GENERATED_BODY()
	
public:
	ACommonCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
