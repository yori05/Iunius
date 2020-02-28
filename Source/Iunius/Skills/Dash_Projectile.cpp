// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash_Projectile.h"
#include "SkillActors/SkillActor.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Components/DamagerComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SkillActors/SkillActor.h"
#include "TimerManager.h"
#include "Components/HealthComponent.h"
#include "Engine/Engine.h"

void UDash_Projectile::HalfWaySpawnActor()
{
	Super::HalfWaySpawnActor();

	auto World = pOwner->GetWorld();
	auto Character = pOwner->GetCharacterOwner();

	if (World && Character && !pActorProjectile)
	{
		pActorProjectile = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillProjectileActor, Character->GetTransform());
		if (pActorProjectile)
		{
			pActorProjectile->SetSkillOwner(this);

			auto Damager = pActorProjectile->GetDamagerComponent();
			if (Damager)
			{
				Damager->ElementDamager = DamageElement;
			}

			pActorProjectile->FSkill_OnBeginOverlap = &USkillBase::execFDetectiocColliderBeginOverlap;
			pActorProjectile->FSkill_OnEndOverlap = &USkillBase::FDetectiocColliderEndOverlap_Static;

			auto ProjectileMC = pActorProjectile->GetProjectileMovementComponent();

			if (ProjectileMC)
			{
				auto vel = pActorProjectile->GetActorForwardVector();
				ProjectileMC->Velocity = DirectionDash * SpeedProjectile;
			}

			FTimerHandle ExecuteTimerHandle;
			pActorProjectile->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, pActorProjectile, &ASkillActor::DestroySkillActor, TimeLifeProjectile);


			pActorProjectile->FinishSpawning(Character->GetTransform());

			DirectionDash *= -1.f;
		}
	}

}
void UDash_Projectile::AfterSpawnActor()
{
	Super::AfterSpawnActor();
	pActorProjectile = nullptr;
}
void UDash_Projectile::FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != pTarget)
	{
		auto Component = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

		if (Component)
		{
			Super::FDetectionColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

			if (pActorProjectile)
			{
				auto Damager = pActorProjectile->GetDamagerComponent();

				if (Damager)
				{
					Damager->DealDamage(DamageValue, Component);
				}
			}
		}
	}
}

void UDash_Projectile::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
