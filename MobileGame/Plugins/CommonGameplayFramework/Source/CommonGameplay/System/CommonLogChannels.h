// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"
class UObject;
COMMONGAMEPLAY_API DECLARE_LOG_CATEGORY_EXTERN(LogCommon, Log, All);



COMMONGAMEPLAY_API FString GetClientServerContextString(UObject* ContextObject = nullptr);