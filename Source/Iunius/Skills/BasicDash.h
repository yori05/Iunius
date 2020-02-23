// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillMovementBase.h"
#include "BasicDash.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UBasicDash : public USkillMovementBase
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere)
	FVector DirectionDash;

public :
	virtual void Initialize() override;

	virtual uint8 RequestExecute() override;

	virtual void Execute() override;

	virtual void TickSkill(float DeltaSecond) override;

	virtual void EndExecute() override;

	virtual uint8 CanBeExecuted() override;

	void SetDirectionDash(const FVector & Direction) { DirectionDash = Direction; }
};
