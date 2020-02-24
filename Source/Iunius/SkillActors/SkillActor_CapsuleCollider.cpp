// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_CapsuleCollider.h"
#include "Components/CapsuleComponent.h"

ASkillActor_CapsuleCollider::ASkillActor_CapsuleCollider()
{
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("DetectionMesh");

	if (ColliderComponent && RootComponent)
		ColliderComponent->SetupAttachment(RootComponent);
}
