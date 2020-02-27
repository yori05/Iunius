// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageEnums.h"
#include "HealthComponent.generated.h"

class UDamagerComponent;
class UHealerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHealthReceiveDamageDelegate, EDamageResult, DamageResult, float, Value, EDamageElement, DamageElement, UDamagerComponent*, DamagerComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHealthReceiveHealDelegate, EDamageResult, DamageResult, float, Value, EDamageElement, DamageElement, UHealerComponent*, DamagerComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHPChangeDelegate, float, HealthPoint, float, HealthPointMax);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthComponentEventDelegate);

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IUNIUS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float HealthPoint;

	UPROPERTY(EditAnywhere)
	float HealthPointMax;

	UPROPERTY(EditAnywhere)
	uint8 bIsImune;

	UPROPERTY(EditAnywhere)
	uint8 bCanBeHeal;

public :
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FHealthReceiveDamageDelegate OnReceiveDamage;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FHealthReceiveHealDelegate OnReceiveHeal;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FHPChangeDelegate OnHPChange;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FHealthComponentEventDelegate OnKilled;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FHealthComponentEventDelegate OnFullLife;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual EDamageResult LooseHP(float Value, EDamageElement Element, UDamagerComponent* DamagerComponent = nullptr, uint8 bAbsorbable = 1);

	UFUNCTION(BlueprintCallable)
		virtual EDamageResult GainHP(float Value, EDamageElement Element, UHealerComponent* HealerComponent = nullptr, uint8 bAbsorbable = 1);

	UFUNCTION(BlueprintCallable)
		uint8 IsImune() { return bIsImune; }

	UFUNCTION(BlueprintCallable)
		void ChangeIsImune(uint8 NewIsImune) { bIsImune = NewIsImune; };

	UFUNCTION(BlueprintCallable)
		float GetHPPercent() { if (HealthPointMax <= 0.0f) return 0.0f; return HealthPoint / HealthPointMax; }
	UFUNCTION(BlueprintCallable)
		float GetHealthPoint() { return HealthPoint; }
	UFUNCTION(BlueprintCallable)
		float GetHealthPointMax() { return HealthPointMax; }

	UFUNCTION(BlueprintCallable)
		uint8 CanBeHeal() { return bCanBeHeal; }

	UFUNCTION(BlueprintCallable)
		void ChangeCanBeHeal(uint8 NewCanBeHeal) { bCanBeHeal = NewCanBeHeal; };

};
