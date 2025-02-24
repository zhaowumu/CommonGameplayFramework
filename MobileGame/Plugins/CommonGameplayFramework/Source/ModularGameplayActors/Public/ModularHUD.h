﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ModularHUD.generated.h"

/** Minimal class that supports extension by game feature plugins */
UCLASS(Blueprintable)
class MODULARGAMEPLAYACTORS_API AModularHUD : public AHUD
{
	GENERATED_BODY()

public:
	//~ Begin AActor Interface
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface
};
