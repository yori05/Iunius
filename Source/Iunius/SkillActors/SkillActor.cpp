// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor.h"
#include "Components/SceneComponent.h"
#include "Skills/SkillBase.h"

// Sets default values
ASkillActor::ASkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

}

// Called when the game starts or when spawned
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillActor::Init(USkillBase* SkillOwner)
{
	pSkillOwner = SkillOwner;
}

bool ASkillActor::AttachRootToActor(USceneComponent * ParentComponent)
{
	return RootComponent->AttachTo(ParentComponent, NAME_None, EAttachLocation::SnapToTarget);
}

void ASkillActor::DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (pSkillOwner)
	{
		pSkillOwner->DetectionColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		OnComponentBeginOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ASkillActor::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (pSkillOwner)
	{
		pSkillOwner->DetectionColliderEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
		OnComponentEndOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	}
}
