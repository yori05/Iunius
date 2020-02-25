// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash_Basic.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Engine/World.h"
#include "SkillActors/SkillActor.h"
#include "TimerManager.h"

void UDash_Basic::AfterSpawnActor()
{
	if (pTarget)
	{
		DirectionDash.Normalize();
		pTarget->MovementDash(DirectionDash, DurationDash, SpeedDash);
	}
}


void UDash_Basic::TickSkill(float DeltaSecond)
{
	Super::TickSkill(DeltaSecond);

	if (bIsExecuted && (!pTarget || !pTarget->IsDashing()))
		EndExecute();
}

void UDash_Basic::EndExecute()
{
	Super::EndExecute();

	LaunchRecuperation();

	if (pActor)
	{
		FTimerHandle ExecuteTimerHandle;
		pActor->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, pActor, &ASkillActor::DestroySkillActor, 0.5f);
		pActor = nullptr;
	}
}

uint8 UDash_Basic::CanBeExecuted()
{
	return Super::CanBeExecuted() && pTarget && pTarget->CanMovementDash();
}
