// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageEnums.h"
#include "DamagerComponent.generated.h"

class UHealthComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDamagerDealDamageDelegate, EDamageResult, Result, float, Value, UHealthComponent *, Target);

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IUNIUS_API UDamagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamagerComponent();

public:	
	UPROPERTY(EditAnywhere)
	EDamageElement ElementDamager = EDamageElement::DamageResult_None;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual EDamageResult DealDamage(float Value, UHealthComponent * Target, uint8 AbsorbableDamage = 1);

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FDamagerDealDamageDelegate OnDealDamage;
};
