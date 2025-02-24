// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonInputComponent.h"



void UCommonInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
