// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManagerComponent.h"
#include "Skills/SkillBase.h"
#include "IuniusCharacter.h"
#include "Skills/BasicDash.h"
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
		it->SetSkillManager(this);
		it->Initialize();
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
 
 	if (!Skills[0]->CanBeExecuted())
 		return;
 
 	for (auto i : Skills)
 	{
 		if (i->IsLocked())
 			return;
 	}
 
	//if (GEngine && GetWorld())
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Emplacement Scene => ")) + GetWorld()->GetLocalURL());

 	auto SkillDash = Cast<UBasicDash, USkillBase>(Skills[0]);
  
	if (!SkillDash)
		return;

 	SkillDash->SetDirectionDash(DirectionDash);
 
 	if (SkillDash->RequestExecute())
		onSkillRequested.Broadcast(0);
}
