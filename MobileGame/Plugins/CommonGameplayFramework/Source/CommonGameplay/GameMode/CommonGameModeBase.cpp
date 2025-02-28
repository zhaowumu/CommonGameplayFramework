// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameModeBase.h"

#include "CommonGameSession.h"
#include "CommonGameState.h"
#include "CommonGameplay/Actor/Character/CommonCharacter.h"
#include "CommonGameplay/Player/CommonPlayerController.h"
#include "CommonGameplay/Player/CommonPlayerState.h"
#include "CommonGameplay/UI/CommonHUD.h"

ACommonGameModeBase::ACommonGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GameStateClass = ACommonGameState::StaticClass();
	GameSessionClass = ACommonGameSession::StaticClass();
	PlayerControllerClass = ACommonPlayerController::StaticClass();
	ReplaySpectatorPlayerControllerClass = ACommonReplayPlayerController::StaticClass();
	PlayerStateClass = ACommonPlayerState::StaticClass();
	DefaultPawnClass = ACommonCharacter::StaticClass();
	HUDClass = ACommonHUD::StaticClass();
}

void ACommonGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Wait for the next frame to give time to initialize startup settings
	// 等到下一帧，以给启动设置初始化留时间
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ACommonGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	// TODO 确定需要Experience概念？
}
