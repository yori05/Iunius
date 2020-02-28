// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Combo.h"

void UAttack_Combo::TickSkill(float DeltaSecond)
{
	if (ComboStack > 0)
	{
		if (ComboTimer <= 0.0f)
		{
			ComboStack = 0;
			OnResetCombo.Broadcast();
		}
		else
		{
			ComboTimer -= DeltaSecond;
		}
	}
}

void UAttack_Combo::ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor)
{
	Super::ResultOfDealDamage(DamageResult, OtherActor);

	if (DamageResult == EDamageResult::DamageResult_Deal || DamageResult == EDamageResult::DamageResult_Kill)
	{
		if (ComboStack < 256)
		ComboStack++;

		if (ComboTimer > ComboDuration * 0.5f)
			ComboTimer = ComboDuration * 2.5f;
		else
			ComboTimer = ComboDuration;

		if (ComboStack == 3)
			OnStackTreeCombo.Broadcast(ComboStack);
		else if (ComboStack == 5)
			OnStackFiveCombo.Broadcast(ComboStack);
		else if (ComboStack == 10)
			OnStatckTenCombo.Broadcast(ComboStack);

	}

}
