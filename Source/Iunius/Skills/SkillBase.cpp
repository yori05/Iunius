// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

void USkillBase::TickSkill(float DeltaSecond)
{
	if (CooldownTimer > 0.0f)
		CooldownTimer -= DeltaSecond;
	
	onTick.Broadcast(DeltaSecond);
}
