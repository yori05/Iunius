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
	//virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	FVector DirectionDash;

	float DashTimer;

	float DashDuration;

public :
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Custom")
		uint8 GetCustomMode() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Climb")
		virtual bool IsDashing() const;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Climb")
		virtual void Dash(const FVector & DirectionToDash);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement|Climb")
		virtual bool CanDash(FHitResult& hitResult) const;

};
