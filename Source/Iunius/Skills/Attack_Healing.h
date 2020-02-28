// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Attack_Basic.h"
#include "Attack_Healing.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttackHealDelegate, EHealResult, Result, AActor*, OtherActor, UAttack_Healing*, SelfSkill);

/**
 * 
 */
UCLASS()
class IUNIUS_API UAttack_Healing : public UAttack_Basic
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, Category = "Attack")
	float HealByHit;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float HealByKill;

	float BoostHeal = 1.0f;

public :
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FAttackHealDelegate OnHealBlocked;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FAttackHealDelegate OnHealSuccessFull;

public:
	virtual void ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor) override;

};
