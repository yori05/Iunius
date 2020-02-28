// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_CapsuleCollider.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ASkillActor_CapsuleCollider::ASkillActor_CapsuleCollider()
{
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("DetectionCapsule");

	if (ColliderComponent && RootComponent)
	{
		ColliderComponent->SetupAttachment(RootComponent);
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor_CapsuleCollider::FDetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor_CapsuleCollider::DetectionColliderEndOverlap);

		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetupAttachment(ColliderComponent);
		}
	}
}
