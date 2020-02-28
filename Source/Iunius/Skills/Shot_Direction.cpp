// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot_Direction.h"
#include "IuniusCharacter.h"
#include "Components/HealthComponent.h"
#include "SkillActors/SkillActor.h"
#include "Components/DamagerComponent.h"
#include "Components/SkillManagerComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UShot_Direction::Execute()
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
			for (uint8 i = 0; i < ShotEject; i++)
			{
				pActor = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillActor, Character->GetTransform());

				if (pActor)
				{
					pActor->SetSkillOwner(this);

					auto Damager = pActor->GetDamagerComponent();
					if (Damager)
					{
						Damager->ElementDamager = DamageElement;
					}

				}

				pActor->FSkill_OnBeginOverlap = &USkillBase::execFDetectiocColliderBeginOverlap;
				pActor->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;

				pActors.Add(pActor);
			}
		}
	}

	HalfWaySpawnActor();
	OnHalfwaySpawnActor.Broadcast();

	FRotator temp;

	if (pActors.Num() > 0)
	{
		temp = pActors[0]->GetActorRotation();
		int nb = pActors.Num();
		auto Character = pOwner->GetCharacterOwner();

		for (int i = 0; i < nb; i++)
		{
			pActors[i]->FinishSpawning(Character->GetTransform());

			if (bLinkActorToTarget)
				pActors[i]->AttachRootToActor(Character->GetCharacterRoot());

			temp.Add(0.0f, 0.0f, 2 * PI / (float)nb * (float)i);
			pActors[i]->SetActorRotation(temp);
			auto ProjectileMC = pActors[i]->GetProjectileMovementComponent();

			if (ProjectileMC)
			{
				auto vel = pActors[i]->GetActorForwardVector();
				ProjectileMC->Velocity = vel * SpeedProjectile;
			}
		}
	}

	AfterSpawnActor();
	OnAfterSpawnActor.Broadcast();

	onExecuted.Broadcast();
}

void UShot_Direction::EndExecute()
{
	bIsExecuted = 0;

	for (auto i : pActors)
	{
		i->Destroy();
	}

	onEndExecution.Broadcast();
}

void UShot_Direction::AfterSpawnActor()
{
	Super::AfterSpawnActor();

	if (GetWorld())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USkillBase::EndExecute, DurationAttack);
	}
}

void UShot_Direction::FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != pTarget)
	{
		auto Component = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (Component)
		{
			Super::FDetectionColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
			auto temp = Cast<ASkillActor>(OverlappedComponent->GetOwner());

			if (temp)
			{
				auto Damager = temp->GetDamagerComponent();

				if (Damager)
				{
					Damager->DealDamage(DamageValue, Component);
					auto temp = Cast<ASkillActor>(OverlappedComponent->GetOwner());
					if (temp)
					{
						pActors.Remove(temp);
						temp->Destroy();
					}
				}
			}
		}
	}
}

void UShot_Direction::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
