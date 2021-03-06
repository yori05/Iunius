// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (HealthPointMax <= 0.0f)
	{
		HealthPointMax = 10.0f;
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EDamageResult UHealthComponent::LooseHP(float Value, ETypeElement Element, UDamagerComponent* DamagerComponent, uint8 bAbsorbable)
{
	if (bIsImune)
	{
		OnReceiveDamage.Broadcast(EDamageResult::DamageResult_Imune, Value, Element, DamagerComponent);
		return EDamageResult::DamageResult_Imune;
	}
	if (Value == 0.0f)
	{
		OnReceiveDamage.Broadcast(EDamageResult::DamageResult_None, Value, Element, DamagerComponent);
		return EDamageResult::DamageResult_None;
	}

	HealthPoint -= Value;

	if (HealthPoint < 0)
		HealthPoint = 0;

	OnHPChange.Broadcast(HealthPoint, HealthPointMax);

	if (HealthPoint <= 0)
	{
		OnKilled.Broadcast();
		OnReceiveDamage.Broadcast(EDamageResult::DamageResult_Kill, Value, Element, DamagerComponent);
		return EDamageResult::DamageResult_Kill;
	}

	OnReceiveDamage.Broadcast(EDamageResult::DamageResult_Deal, Value, Element, DamagerComponent);
	return EDamageResult::DamageResult_Deal;
}

EHealResult UHealthComponent::GainHP(float Value, ETypeElement Element, UHealerComponent* HealerComponent, uint8 bAbsorbable)
{
	if (!bCanBeHeal)
	{
		OnReceiveHeal.Broadcast(EHealResult::HealResult_Impossible, Value, Element, HealerComponent);
		return EHealResult::HealResult_Impossible;
	}
	if (Value == 0.0f)
	{
		OnReceiveHeal.Broadcast(EHealResult::HealResult_None, Value, Element, HealerComponent);
		return EHealResult::HealResult_None;
	}

	HealthPoint += Value;
	if (HealthPoint > HealthPointMax)
		HealthPoint = HealthPointMax;

	if (HealthPoint > HealthPointMax)
	{
		OnFullLife.Broadcast();
		OnReceiveHeal.Broadcast(EHealResult::HealResult_Full, Value, Element, HealerComponent);
		return EHealResult::HealResult_Full;
	}

	OnReceiveHeal.Broadcast(EHealResult::HealResult_Deal, Value, Element, HealerComponent);
	return EHealResult::HealResult_Deal;

}
