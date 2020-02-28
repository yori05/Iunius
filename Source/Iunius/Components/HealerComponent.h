// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IuniusEnums.h"
#include "HealerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealerGiveHPDelegate, EHealResult, Result, float, Value, UHealthComponent *, Target);

class UHealthComponent;
/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IUNIUS_API UHealerComponent : public UActorComponent
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, Category = "Element")
	ETypeElement ElementHeal;

public :
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FHealerGiveHPDelegate OnGiveHeal;

public:	
	// Sets default values for this component's properties
	UHealerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual EHealResult GiveHeal(float Value, UHealthComponent * Target, uint8 AbosbableHeal = true);

};
