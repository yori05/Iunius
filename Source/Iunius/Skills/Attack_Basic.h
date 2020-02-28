// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/SkillBase.h"
#include "Attack_Basic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttackTouchDelegate, EDamageResult, Result, AActor*, OtherActor, UAttack_Basic*, SelfSkill);

/**
 * 
 */
UCLASS()
class IUNIUS_API UAttack_Basic : public USkillBase
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, Category = "Attack")
	FVector OffsetSpawning = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	FVector DirectionAttack = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float DepthSpawing = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float TimeAttack = 0.50f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float PowEjection = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float BoostEjectionKill = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float BoostEjectionHit = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float BoostEjectionAbsobed = 0.5f;

	float BoostDamage = 1.0f;

public :
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAttackTouchDelegate OnAttackSuccessfull;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAttackTouchDelegate OnAttackBlocked;

protected :
	virtual void HalfWaySpawnActor() override;
	virtual void AfterSpawnActor() override;
	virtual void EndExecute() override;

	virtual void ResultOfDealDamage(EDamageResult DamageResult, AActor* OtherActor);

public :
	virtual void FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintCallable)
	void SetDirectionAttack(const FVector& NewDirectionAttack) { DirectionAttack = NewDirectionAttack; }
};
