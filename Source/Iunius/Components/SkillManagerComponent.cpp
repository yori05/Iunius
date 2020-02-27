// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManagerComponent.h"
#include "Skills/SkillBase.h"
#include "IuniusCharacter.h"
#include "Skills/Dash_Basic.h"
#include "Skills/Attack_Basic.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USkillManagerComponent::USkillManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	pOwnerCharacter = Cast<AIuniusCharacter>(GetOwner());

	for (auto it : Skills)
	{
		it->Initialize(this);
	}
}


// Called every frame
void USkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto it : Skills)
	{
		it->TickSkill(DeltaTime);
	}

	// ...
}

uint8 USkillManagerComponent::IsASkillExecuting()
{
	for (auto it : Skills)
	{
		if (it->IsExecuted())
			return 1;
	}

	return 0;
}

void USkillManagerComponent::SkillRequested(const int32 SkillIndex)
{
	if (!Skills.IsValidIndex(SkillIndex))
		return;

	if (!Skills[SkillIndex]->CanBeExecuted())
		return;

	for (auto i : Skills)
	{
		if (i->IsLocked())
			return;
	}

	Skills[SkillIndex]->RequestExecute();
	onSkillRequested.Broadcast(SkillIndex);
}

void USkillManagerComponent::DashRequested(const FVector & DirectionDash)
{
 	if (!Skills.IsValidIndex(0))
 		return;
 
	Skills[0]->SetTarget(pOwnerCharacter);

 	if (!Skills[0]->CanBeExecuted())
 		return;
 
 	for (auto i : Skills)
 	{
 		if (i->IsLocked())
 			return;
 	}
 
 	auto SkillDash = Cast<UDash_Basic, USkillBase>(Skills[0]);
  
	if (!SkillDash)
		return;

 	SkillDash->SetDirectionDash(DirectionDash);
 
 	if (SkillDash->RequestExecute())
		onSkillRequested.Broadcast(1);
	else
		onSkillRequested.Broadcast(0);
}

void USkillManagerComponent::AttackRequested(const FVector& DirectionAttack)
{
	if (!Skills.IsValidIndex(1))
		return;

	Skills[1]->SetTarget(pOwnerCharacter);

	if (!Skills[1]->CanBeExecuted())
		return;

	for (auto i : Skills)
	{
		if (i->IsLocked())
			return;
	}

	auto SkillAttack = Cast<UAttack_Basic, USkillBase>(Skills[1]);

	if (!SkillAttack)
		return;

	SkillAttack->SetDirectionAttack(DirectionAttack);

	if (SkillAttack->RequestExecute())
		onSkillRequested.Broadcast(1);
	else
		onSkillRequested.Broadcast(0);
}

USkillBase* USkillManagerComponent::GetDashSkill()
{
	if (!Skills.IsValidIndex(0))
		return nullptr;

	return Skills[0];
}
