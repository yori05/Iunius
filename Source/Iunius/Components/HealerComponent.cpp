// Fill out your copyright notice in the Description page of Project Settings.


#include "HealerComponent.h"
#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealerComponent::UHealerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EHealResult UHealerComponent::GiveHeal(float Value, UHealthComponent * Target, uint8 AbosbableHeal)
{
	auto Result = Target->GainHP(Value, ElementHeal, this);
	OnGiveHeal.Broadcast(Result, Value, Target);

	return Result;

}
