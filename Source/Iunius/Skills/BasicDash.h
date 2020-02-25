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
class IUNIUS_API UBasicDash : public USkillBase
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere)
	FVector DirectionDash;
	
public:
	virtual void AfterSpawnActor() override;

	virtual void TickSkill(float DeltaSecond) override;

	virtual void EndExecute() override;

	virtual uint8 CanBeExecuted() override;

	UFUNCTION(BlueprintCallable)
	void SetDirectionDash(const FVector & Direction) { DirectionDash = Direction; }

};
