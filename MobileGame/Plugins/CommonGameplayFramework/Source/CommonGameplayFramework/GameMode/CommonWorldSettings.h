// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "CommonWorldSettings.generated.h"

/**
 * The default world settings object, used primarily to set the default gameplay experience to use when playing on this map
 * 默认世界设置对象，主要用于设置在此地图上玩游戏时使用的默认游戏体验
 * 每个 Level 中只能有一个 AWorldSettings 实例。它始终位于 ULevel::Actors[0] 的位置，方便快速访问。
 */
UCLASS()
class COMMONGAMEPLAYFRAMEWORK_API ACommonWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	ACommonWorldSettings(const FObjectInitializer& ObjectInitializer);
};
