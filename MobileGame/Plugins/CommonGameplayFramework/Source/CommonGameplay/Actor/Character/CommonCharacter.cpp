// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonCharacter.h"

#include "Components/CapsuleComponent.h"

static FName NAME_CommonCharacterCollisionProfile_Capsule(TEXT("CommonPawnCapsule"));
static FName NAME_CommonCharacterCollisionProfile_Mesh(TEXT("CommonPawnMesh"));

ACommonCharacter::ACommonCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Avoid ticking characters if possible.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetNetCullDistanceSquared(900000000.0f);

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	CapsuleComp->SetCollisionProfileName(NAME_CommonCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.
	MeshComp->SetCollisionProfileName(NAME_CommonCharacterCollisionProfile_Mesh);
}
