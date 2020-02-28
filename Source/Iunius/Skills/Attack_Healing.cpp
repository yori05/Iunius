// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Healing.h"
#include "GameFramework/Character.h"
#include "SkillActors/SkillActor.h"
#include "Components/HealerComponent.h"
#include "IuniusCharacter.h"

void UAttack_Healing::ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor)
{
	Super::ResultOfDealDamage(DamageResult, OtherActor);

	if (DamageResult == EDamageResult::DamageResult_Deal || DamageResult == EDamageResult::DamageResult_Deal)
	{
		auto Healer = pActor->GetHealerComponent();
		auto result = Healer->GiveHeal(HealByHit * BoostHeal, pTarget->GetHealthComponent());

		if (result == EHealResult::HealResult_Absorbed || result == EHealResult::HealResult_Deal || result == EHealResult::HealResult_Full)
		{
			OnHealSuccessFull.Broadcast(result, OtherActor, this);
		}
		else
		{
			OnHealBlocked.Broadcast(result, OtherActor, this);
		}
	}
}
