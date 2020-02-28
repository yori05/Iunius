// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Attack_Basic.h"
#include "Attack_Combo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackComboStackDelegate, uint8, NbStack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetComboStackDelegate);

/**
 * 
 */
UCLASS()
class IUNIUS_API UAttack_Combo : public UAttack_Basic
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleAnywhere)
	uint8 ComboStack = 0;

	UPROPERTY(VisibleAnywhere)
		float ComboTimer = 0.0f;

	UPROPERTY(EditAnywhere)
		float ComboDuration = 4.0f;

public :
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FAttackComboStackDelegate OnStackTreeCombo;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FAttackComboStackDelegate OnStackFiveCombo;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FAttackComboStackDelegate OnStatckTenCombo;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FResetComboStackDelegate OnResetCombo;

protected : 
	virtual void TickSkill(float DeltaSecond) override;
	virtual void ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor) override;
};
