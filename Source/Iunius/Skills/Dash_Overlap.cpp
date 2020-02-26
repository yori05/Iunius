// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash_Overlap.h"
#include "IuniusCharacter.h"
#include "Components/HealthComponent.h"
#include "SkillActors/SkillActor.h"
#include "Components/DamagerComponent.h"

void UDash_Overlap::HalfWaySpawnActor()
{
	Super::HalfWaySpawnActor();

	pActor->FSkill_OnBeginOverlap = &USkillBase::FDetectiocColliderBeginOverlap_Static;
	pActor->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;
}

void UDash_Overlap::DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
					Damager->DealDamage(DamageValue, Component);
				}
			}
		}
	}
}

void UDash_Overlap::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

