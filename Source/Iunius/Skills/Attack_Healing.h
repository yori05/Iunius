// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Attack_Basic.h"
#include "Attack_Healing.generated.h"

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

public:
	virtual void ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor) override;

};
