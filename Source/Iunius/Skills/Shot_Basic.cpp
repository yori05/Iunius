// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot_Basic.h"
#include "IuniusCharacter.h"
#include "Components/HealthComponent.h"
#include "SkillActors/SkillActor.h"
#include "Components/DamagerComponent.h"

void UShot_Basic::HalfWaySpawnActor()
{
	Super::HalfWaySpawnActor();

	pActor->FSkill_OnBeginOverlap = &USkillBase::execFDetectiocColliderBeginOverlap;
	pActor->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;
}

void UShot_Basic::FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void UShot_Basic::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

