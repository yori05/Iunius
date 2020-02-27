// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UDamagerComponent::UDamagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EDamageResult UDamagerComponent::DealDamage(float Value, UHealthComponent * Target, uint8 AbosbableDamage)
{
	auto Result = Target->LooseHP(Value, ElementDamager, this);
	OnDealDamage.Broadcast(Result, Value, Target);

	return Result;
}
