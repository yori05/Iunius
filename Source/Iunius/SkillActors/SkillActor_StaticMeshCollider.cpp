// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_StaticMeshCollider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"

ASkillActor_StaticMeshCollider::ASkillActor_StaticMeshCollider()
{
	ColliderComponent = CreateDefaultSubobject<UStaticMeshComponent>("DetectionMesh");

	if (ColliderComponent && RootComponent)
	{
		ColliderComponent->SetupAttachment(RootComponent);
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor_StaticMeshCollider::DetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor_StaticMeshCollider::DetectionColliderEndOverlap);

		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetupAttachment(ColliderComponent);
		}
	}
}