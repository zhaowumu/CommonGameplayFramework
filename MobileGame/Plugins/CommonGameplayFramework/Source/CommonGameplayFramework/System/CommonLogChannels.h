// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"
class UObject;
COMMONGAMEPLAYFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogCommon, Log, All);



COMMONGAMEPLAYFRAMEWORK_API FString GetClientServerContextString(UObject* ContextObject = nullptr);