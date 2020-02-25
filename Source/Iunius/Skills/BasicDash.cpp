// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicDash.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Engine/World.h"

void UBasicDash::AfterSpawnActor()
{
	if (pTarget)
	{
		DirectionDash.Normalize();
		pTarget->MovementDash(DirectionDash);
	}
}


void UBasicDash::TickSkill(float DeltaSecond)
{
	Super::TickSkill(DeltaSecond);

	if (bIsExecuted && (!pTarget || !pTarget->IsDashing()))
		EndExecute();
}

void UBasicDash::EndExecute()
{
	Super::EndExecute();

	LaunchRecuperation();
}

uint8 UBasicDash::CanBeExecuted()
{
	return Super::CanBeExecuted() && pTarget && pTarget->CanMovementDash();
}
