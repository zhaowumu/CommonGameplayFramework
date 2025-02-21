// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "Kismet/BlueprintPlatformLibrary.h"

#include "CommonGameInstance.generated.h"

enum class ECommonUserAvailability : uint8;
enum class ECommonUserPrivilege : uint8;

class FText;
class UCommonUserInfo;
class UCommonSession_SearchResult;
struct FOnlineResultInformation;
class ULocalPlayer;
class USocialManager;
class UObject;
struct FFrame;
struct FGameplayTag;


/*
 * 用于处理游戏实例的通用逻辑，包括用户管理、会话管理、错误处理等
 * 抽象类，不能被直接实例化，并且它的配置信息存储在 Game 配置文件中。
 */
UCLASS(Abstract, Config = Game)
class COMMONGAME_API UCommonGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCommonGameInstance(const FObjectInitializer& ObjectInitializer);
	
	/** Handles errors/warnings from CommonUser, can be overridden per game
	 * 处理来自CommonUser的错误/警告，可以按游戏覆盖
	 */
	UFUNCTION()
	virtual void HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message);

	/*
	 * 处理权限已更改
	 */
	UFUNCTION()
	virtual void HandlePrivilegeChanged(const UCommonUserInfo* UserInfo, ECommonUserPrivilege Privilege, ECommonUserAvailability OldAvailability, ECommonUserAvailability NewAvailability);

	/*
	 * 处理用户已初始化
	 */
	UFUNCTION()
	virtual void HandlerUserInitialized(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error, ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext);

	/** Call to reset user and session state, usually because a player has been disconnected
	 * 重置用户和会话状态，通常是因为玩家已断开连接
	 */
	virtual void ResetUserAndSessionState();

	/**
	 * Requested Session Flow
	 *   Something requests the user to join a specific session (for example, a platform overlay via OnUserRequestedSession).
	 *   This request is handled in SetRequestedSession.
	 *   Check if we can join the requested session immediately (CanJoinRequestedSession).  If we can, join the requested session (JoinRequestedSession)
	 *   If not, cache the requested session and instruct the game to get into a state where the session can be joined (ResetGameAndJoinRequestedSession)
	 */
	/** Handles user accepting a session invite from an external source (for example, a platform overlay). Intended to be overridden per game. */
	virtual void OnUserRequestedSession(const FPlatformUserId& PlatformUserId, UCommonSession_SearchResult* InRequestedSession, const FOnlineResultInformation& RequestedSessionResult);

	/** Handles OSS request that the session be destroyed */
	virtual void OnDestroySessionRequested(const FPlatformUserId& PlatformUserId, const FName& SessionName);

	/** Get the requested session */
	UCommonSession_SearchResult* GetRequestedSession() const { return RequestedSession; }
	/** Set (or clear) the requested session. When this is set, the requested session flow begins. */
	virtual void SetRequestedSession(UCommonSession_SearchResult* InRequestedSession);
	/** Checks if the requested session can be joined. Can be overridden per game. */
	virtual bool CanJoinRequestedSession() const;
	/** Join the requested session */
	virtual void JoinRequestedSession();
	/** Get the game into a state to join the requested session */
	virtual void ResetGameAndJoinRequestedSession();
	
	virtual int32 AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId) override;
	virtual bool RemoveLocalPlayer(ULocalPlayer* ExistingPlayer) override;
	virtual void Init() override;
	virtual void ReturnToMainMenu() override;

private:
	/** This is the primary player*/
	TWeakObjectPtr<ULocalPlayer> PrimaryPlayer;
	/** Session the player has requested to join */
	UPROPERTY()
	TObjectPtr<UCommonSession_SearchResult> RequestedSession;
};