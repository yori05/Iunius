// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_BoxCollider.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ASkillActor_BoxCollider::ASkillActor_BoxCollider()
{
	ColliderComponent = CreateDefaultSubobject<UBoxComponent>("DetectionBox");

	if (ColliderComponent && RootComponent)
	{
		ColliderComponent->SetupAttachment(RootComponent);
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor_BoxCollider::FDetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor_BoxCollider::DetectionColliderEndOverlap);

		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetupAttachment(ColliderComponent);
		}
	}
}
