// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IuniusCharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMovementDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovementVectorDelegate, FVector, Direction);

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

	UPROPERTY(VisibleAnywhere, Category = "Dash")
	float DashTimer = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Dash")
		float DashDuration = 0.25f;

	UPROPERTY(VisibleAnywhere, Category = "Dash")
		float DashSpeed = 2500.0f;

public :
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Custom")
		uint8 GetCustomMode() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual bool IsDashing() const;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FMovementVectorDelegate OnDash;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual void Dash(const FVector & DirectionToDash, float Duration = 0.25f, float Speed = 2500.0f);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FMovementDelegate OnStopDash;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual void StopDash();

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash")
		virtual bool CanDash() const;

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Dash" )
	virtual void PhysDash(float deltaTime, int32 Iterations);

	float GetDashRemanantTime() { return (DashTimer <= 0.f) ? 0.0f : DashTimer; }
	float GetDashRemanantTimeRatio() { return (DashTimer <= 0.f || DashDuration < 0.0001f) ? 0.0f : DashTimer / DashDuration; }
	float GetDashDuration() { return DashDuration; }
	float GetDashSpeed() { return DashSpeed; }

};
