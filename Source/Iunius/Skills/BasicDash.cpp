// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicDash.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Components/IuniusCharacterMovementComponent.h"
#include "Engine/World.h"

void UBasicDash::Initialize()
{
	Super::Initialize();
	pMovementComponent = pOwner->GetCharacterOwner()->GetCustomCharacterMovement();
}

uint8 UBasicDash::RequestExecute()
{
	if (!CanBeExecuted())
	{
		onRequestExecuted.Broadcast(false);
		return 0;
	}

	onRequestExecuted.Broadcast(true);
	Execute();
	return 1;
}

void UBasicDash::Execute()
{
	if (!CanBeExecuted())
	{
		return;
	}

	Super::Execute();

	FinishExecute();
}

void UBasicDash::FinishExecute()
{
	if (pActor && pActor->AttachRootToActor(pOwner->GetCharacterOwner()->GetCharacterRoot()))
	{
		pActor->FinishSpawning(pOwner->GetCharacterOwner()->GetTransform());
		DirectionDash.Normalize();
		pMovementComponent->Dash(DirectionDash);
	}
}


void UBasicDash::TickSkill(float DeltaSecond)
{
	Super::TickSkill(DeltaSecond);

	if (bIsExecuted && (!pMovementComponent || !pMovementComponent->IsDashing()))
		EndExecute();
}

void UBasicDash::EndExecute()
{
	Super::EndExecute();

	LaunchRecuperation();
}

uint8 UBasicDash::CanBeExecuted()
{
	return Super::CanBeExecuted() && pMovementComponent && pMovementComponent->CanDash();
}
