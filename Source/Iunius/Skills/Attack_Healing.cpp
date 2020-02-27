// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Healing.h"
#include "GameFramework/Character.h"
#include "SkillActors/SkillActor.h"
#include "Components/HealerComponent.h"
#include "IuniusCharacter.h"

void UAttack_Healing::ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor)
{
	Super::ResultOfDealDamage(DamageResult, OtherActor);
	//if (DamageResult == EDamageResult::DamageResult_Deal)
	//{
	//	auto Healer = pActor->GetHealerComponent();
	//	Healer->
	//	pTarget->GetHealthComponent()
	//}
	//if (DamageResult == EDamageResult::DamageResult_Deal || DamageResult == EDamageResult::DamageResult_Kill || DamageResult == EDamageResult::DamageResult_Absorbed)
	//{
	//	auto Character = Cast<ACharacter>(OtherActor);
	//	float Ratio = (DamageResult == EDamageResult::DamageResult_Absorbed) ? 0.5f : (DamageResult == EDamageResult::DamageResult_Kill) ? 2.0f : 1.0f;
	//	if (Character)
	//	{
	//		Character->LaunchCharacter(DirectionAttack * PowEjection * Ratio, true, false);
	//	}
	//}
}
