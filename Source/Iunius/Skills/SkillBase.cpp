// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "Engine/World.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "SkillActors/SkillActor.h"
#include "Engine/Engine.h"
#include "Components/DamagerComponent.h"

void USkillBase::Initialize(USkillManagerComponent* _Owner)
{
	onInitialize.Broadcast(); 
	SetSkillManager(_Owner);
}

void USkillBase::Execute() 
{ 
	bIsExecuted = 1;

	BeforeSpawnActor();
	OnBeforeSpawnActor.Broadcast();

	if (pOwner && pOwner->GetWorld() && pOwner->GetCharacterOwner() && TypeOfSkillActor)
	{
		auto World = pOwner->GetWorld();
		auto Character = pOwner->GetCharacterOwner();

		if (World && Character && !pActor)
		{
			pActor = World->SpawnActorDeferred<ASkillActor>(TypeOfSkillActor, Character->GetTransform());
			if (pActor)
			{
				pActor->SetSkillOwner(this);

				auto Damager = pActor->GetDamagerComponent();
				if (Damager)
				{
					Damager->ElementDamager = DamageElement;
				}

			}
		}
	}

	HalfWaySpawnActor();
	OnHalfwaySpawnActor.Broadcast();

	if (pActor)
	{

		auto Character = pOwner->GetCharacterOwner();
		pActor->FinishSpawning(Character->GetTransform());
		
		if (bLinkActorToTarget)
			pActor->AttachRootToActor(Character->GetCharacterRoot());
	}

	AfterSpawnActor();
	OnAfterSpawnActor.Broadcast();

	onExecuted.Broadcast();
}

void USkillBase::BeforeSpawnActor()
{
	//Executed before the Deferred Spawn of the SkillActor
}

void USkillBase::HalfWaySpawnActor()
{
	//Executed when the SkillActor is Spawn but he don't have finish his Spawning 

}

void USkillBase::AfterSpawnActor()
{
	//Executed after the SkillActor as finish his Spawning 

}

void USkillBase::EndExecute()
{ 
	bIsExecuted = 0; 

	if (bKillActorEndExecute && pActor)
	{
		pActor->Destroy();
		pActor = nullptr;
	}

	onEndExecution.Broadcast(); 
}

void USkillBase::TickSkill(float DeltaSecond)
{
	if (CooldownTimer > 0.0f)
		CooldownTimer -= DeltaSecond;
	
	onTick.Broadcast(DeltaSecond);
}

void USkillBase::DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnSkillActorBeginOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (pActor)
		pActor->OnColliderBeginOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void USkillBase::DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnSkillActorEndOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (pActor)
		pActor->OnColliderEndOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

uint8 USkillBase::RequestExecute()
{
	if (CanBeExecuted()) 
	{
	Execute(); 
		onRequestExecuted.Broadcast(1); 
		return 1; 
	} 

	onRequestExecuted.Broadcast(0); 
	return 0;
}
