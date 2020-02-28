// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot_DualInterp.h"
#include "IuniusCharacter.h"
#include "Components/HealthComponent.h"
#include "SkillActors/SkillActor.h"
#include "Components/DamagerComponent.h"
#include "Components/SkillManagerComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UShot_DualInterp::Execute()
{
	bIsExecuted = 1;

	BeforeSpawnActor();
	OnBeforeSpawnActor.Broadcast();

	if (pOwner && pOwner->GetWorld() && pOwner->GetCharacterOwner() && TypeOfSkillActor)
	{
		auto World = pOwner->GetWorld();
		auto Character = pOwner->GetCharacterOwner();

		if (World && Character && !pActor)
		{
			pActor = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillActor, Character->GetTransform());
			pActorSecondary = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillActor, Character->GetTransform());
			if (pActor)
			{
				pActor->SetSkillOwner(this);

				auto Damager = pActor->GetDamagerComponent();
				if (Damager)
				{
					Damager->ElementDamager = DamageElement;
				}

				pActor->FSkill_OnBeginOverlap = &USkillBase::execFDetectiocColliderBeginOverlap;
				pActor->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;

			}
			if (pActorSecondary)
			{
				pActorSecondary->SetSkillOwner(this);

				auto Damager = pActorSecondary->GetDamagerComponent();
				if (Damager)
				{
					Damager->ElementDamager = DamageElement;
				}


				pActorSecondary->FSkill_OnBeginOverlap = &USkillBase::execFDetectiocColliderBeginOverlap;
				pActorSecondary->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;
			
			}
		}
	}

	HalfWaySpawnActor();
	OnHalfwaySpawnActor.Broadcast();

	if (pActor)
	{

		auto Character = pOwner->GetCharacterOwner();
		pActor->FinishSpawning(Character->GetTransform());

		if (bLinkActorToTarget)
			pActor->AttachRootToActor(Character->GetCharacterRoot());
	}

	AfterSpawnActor();
	OnAfterSpawnActor.Broadcast();

	onExecuted.Broadcast();
}

void UShot_DualInterp::EndExecute()
{
	bIsExecuted = 0;

	if (bKillActorEndExecute && pActor)
	{
		pActor->Destroy();
		pActor = nullptr;
	}
	if (bKillActorEndExecute && pActorSecondary)
	{
		pActorSecondary->Destroy();
		pActorSecondary = nullptr;
	}

	onEndExecution.Broadcast();
}

void UShot_DualInterp::AfterSpawnActor()
{
	Super::AfterSpawnActor();

	auto Interp = pActor->GetInterpToMovementComponent();

	if (Interp)
	{
		Interp->Duration = DurationAttack;
	}

	Interp = pActorSecondary->GetInterpToMovementComponent();

	if (Interp)
	{
		Interp->Duration = DurationAttack;
	}

	auto Rotator = pActorSecondary->GetActorRotation();
	Rotator.Add(0.0f, PI, 0.0f);
	pActorSecondary->SetActorRotation(Rotator);

	if (GetWorld())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USkillBase::EndExecute, DurationAttack);
	}
}

void UShot_DualInterp::FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != pTarget)
	{
		auto Component = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (Component)
		{
			Super::FDetectionColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

			if (pActor)
			{
				auto Damager = pActor->GetDamagerComponent();

				if (Damager)
				{
					Damager->DealDamage(DamageValue, Component);
					OverlappedComponent->GetOwner()->Destroy();
				}
			}
		}
	}
}

void UShot_DualInterp::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != pTarget)
	{
		auto Component = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (Component)
		{
			Super::DetectionColliderEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
		}
	}
}
