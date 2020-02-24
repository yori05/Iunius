// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillMovementBase.h"
#include "SkillMonoActorBase.h"
#include "BasicDash.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UBasicDash : public USkillMonoActorBase
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere)
	FVector DirectionDash;
	UIuniusCharacterMovementComponent *pMovementComponent;
	
	//Called last in the execution function (after the spawn of the actor)
	UFUNCTION(BlueprintCallable)
	virtual void FinishExecute();

public:
	UFUNCTION(BlueprintCallable)
	void SetMovementComponent(UIuniusCharacterMovementComponent * MovementComponent) {
		pMovementComponent = MovementComponent;
	};
	virtual void Initialize() override;

	virtual uint8 RequestExecute() override;

	virtual void Execute() override;
	virtual void TickSkill(float DeltaSecond) override;

	virtual void EndExecute() override;

	virtual uint8 CanBeExecuted() override;

	UFUNCTION(BlueprintCallable)
	void SetDirectionDash(const FVector & Direction) { DirectionDash = Direction; }
};
