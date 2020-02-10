// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IuniusCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementModeCustom : uint8
{
	/** None (mouvement is disabled).*/
	CUSTOM_None UMETA(DisplayName = "None"),

	CUSTOM_Dash UMETA(DisplayName = "Dash"),

	CUSTOM_Max UMETA(Hidden),
};

/**
 * 
 */
UCLASS()
class IUNIUS_API UIuniusCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
protected :

	FVector DirectionDash = FVector::ForwardVector;

	float DashTimer = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dash")
		float DashDuration = 0.25f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dash")
		float SpeedDash = 3000.0f;

public :
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Custom")
		uint8 GetCustomMode() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual bool IsDashing() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual void Dash(const FVector & DirectionToDash);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual void StopDash();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual bool CanDash(FHitResult& hitResult) const;

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash" )
	virtual void PhysDash(float deltaTime, int32 Iterations);

};
