// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor.h"
#include "Components/SceneComponent.h"
#include "Skills/SkillBase.h"
#include "Components/DamagerComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASkillActor::ASkillActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	DamagerComponent = CreateDefaultSubobject<UDamagerComponent>("DamagerComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if (RootComponent && StaticMeshComponent)
	{
		StaticMeshComponent->SetupAttachment(RootComponent);
		StaticMeshComponent->SetCollisionProfileName("NoCollision");
	}
}

// Called when the game starts or when spawned
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ColliderComponent)
	{
		ColliderComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillActor::FDetectionColliderBeginOverlap);
		ColliderComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ASkillActor::DetectionColliderEndOverlap);
	}
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

bool ASkillActor::AttachRootToActor(USceneComponent * ComponentLinked)
{
	return RootComponent->AttachToComponent(ComponentLinked, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ASkillActor::FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (pSkillOwner && FSkill_OnBeginOverlap)
		FSkill_OnBeginOverlap(pSkillOwner, OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ASkillActor::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (pSkillOwner && FSkill_OnEndOverlap)
		FSkill_OnEndOverlap(pSkillOwner, OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void ASkillActor::DestroySkillActor()
{
	Destroy();
}