// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_SphereCollider.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


ASkillActor_SphereCollider::ASkillActor_SphereCollider()
{
	ColliderComponent = CreateDefaultSubobject<USphereComponent>("DetectionSphere");

	if (ColliderComponent && RootComponent)
	{
		ColliderComponent->SetupAttachment(RootComponent);
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor_SphereCollider::DetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor_SphereCollider::DetectionColliderEndOverlap);

		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetupAttachment(ColliderComponent);
		}
	}
}