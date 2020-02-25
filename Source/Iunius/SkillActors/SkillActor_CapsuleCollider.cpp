// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_CapsuleCollider.h"
#include "Components/CapsuleComponent.h"

ASkillActor_CapsuleCollider::ASkillActor_CapsuleCollider()
{
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("DetectionMesh");

	if (ColliderComponent && RootComponent)
	{
		ColliderComponent->SetupAttachment(RootComponent);
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor_CapsuleCollider::DetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor_CapsuleCollider::DetectionColliderEndOverlap);
	}
}
