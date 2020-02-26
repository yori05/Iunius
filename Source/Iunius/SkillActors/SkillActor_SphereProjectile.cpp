// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_SphereProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASkillActor_SphereProjectile::ASkillActor_SphereProjectile()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	if (ProjectileMovementComponent && RootComponent)
	{
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
		ProjectileMovementComponent->bInitialVelocityInLocalSpace = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
}