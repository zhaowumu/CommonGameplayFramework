// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPawn.h"
#include "CommonPawn.generated.h"

/*
 * 通用Pawn
 */
UCLASS()
class COMMONGAMEPLAYFRAMEWORK_API ACommonPawn : public AModularPawn
{
	GENERATED_BODY()

public:
	
	ACommonPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


};
