// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillMonoActorBase.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Components/IuniusCharacterMovementComponent.h"
#include "Engine/World.h"

void USkillMonoActorBase::Execute()
{
	Super::Execute();
	if (pOwner && pOwner->GetWorld() && pOwner->GetCharacterOwner())
	{
		auto World = pOwner->GetWorld();
		auto Character = pOwner->GetCharacterOwner();

		if (World && Character && !pActor)
		{
			pActor = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillActor, Character->GetTransform());
		}
	}
}

void USkillMonoActorBase::EndExecute()
{
	Super::EndExecute();
	
	if (pActor)
	{
		pActor->Destroy();
		pActor = nullptr;
	}
}
