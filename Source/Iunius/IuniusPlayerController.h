// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IuniusPlayerController.generated.h"

UCLASS()
class AIuniusPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AIuniusPlayerController();

	virtual void SetPawn(APawn* InPawn) override;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */

	uint8 bWantToDash : 1;

	uint8 bWantToAttack : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	UPROPERTY(VisibleAnywhere)
	FVector MovementVectorThisFrame = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	FVector DirectionCursor = FVector::ZeroVector;

	class AIuniusCharacter* MyPawn = nullptr;
 
	void MoveFromMovementVector(float DeltaTime);

	void MoveForward(float _value);

	void MoveRight(float _value);

	void Dash();

	void Attack();
};


