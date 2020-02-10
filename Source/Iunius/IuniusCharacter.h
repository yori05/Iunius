// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IuniusCharacter.generated.h"

UCLASS(Blueprintable)
class AIuniusCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AIuniusCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UFUNCTION(BlueprintCallable)
	void Dash(const FVector & DirectionToDash);

	//UFUNCTION(BlueprintCallable)
	//float GetMoveSpeed() ;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

protected :

	UPROPERTY(EditAnywhere)
		class UIuniusCharacterMovementComponent * CustomCharacterMC;

	//UPROPERTY(VisibleAnywhere, EditAnywhere)
	//class UCharacterMovementComponent * CharacterMovementComponent;

	//UPROPERTY(VisibleAnywhere, EditAnywhere)
	//	float MoveSpeed = 200.0f;
};

