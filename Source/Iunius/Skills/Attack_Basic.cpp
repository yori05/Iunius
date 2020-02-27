// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Basic.h"
#include "SkillActors/SkillActor.h"
#include "Components/HealthComponent.h"
#include "Components/DamagerComponent.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "TimerManager.h"

void UAttack_Basic::HalfWaySpawnActor()
{
	Super::HalfWaySpawnActor();

	pActor->FSkill_OnBeginOverlap = &USkillBase::FDetectiocColliderBeginOverlap_Static;
	pActor->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;
}

void UAttack_Basic::AfterSpawnActor()
{
	Super::AfterSpawnActor();

	pTarget->ChangeCanRotate(false);
	pActor->SetActorLocation(pOwner->GetCharacterOwner()->GetActorLocation() + OffsetSpawning + DirectionAttack * DepthSpawing);

	FTimerHandle ExecuteTimerHandle;
	pActor->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, this, &USkillBase::EndExecute, TimeAttack);
}

void UAttack_Basic::EndExecute()
{
	Super::EndExecute();
	pTarget->ChangeCanRotate(true);
}

void UAttack_Basic::DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != pTarget)
	{
		auto Component = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (Component)
		{
			Super::DetectionColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

			if (pActor)
			{
				auto Damager = pActor->GetDamagerComponent();

				if (Damager)
				{
					auto Result = Damager->DealDamage(DamageValue, Component);
					ResultOfDealDamage(Result, OtherActor);

					
				}
			}
		}
	}
}

void UAttack_Basic::ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor)
{
	if (DamageResult == EDamageResult::DamageResult_Deal || DamageResult == EDamageResult::DamageResult_Kill || DamageResult == EDamageResult::DamageResult_Absorbed)
	{
		auto Character = Cast<ACharacter>(OtherActor);
		float Ratio = (DamageResult == EDamageResult::DamageResult_Absorbed) ? 0.5f : (DamageResult == EDamageResult::DamageResult_Kill) ? 2.0f : 1.0f;
		if (Character)
		{
			Character->LaunchCharacter(DirectionAttack * PowEjection * Ratio, true, false);
		}
	}
}

void UAttack_Basic::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

