// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/SkillBase.h"
#include "Dash_Basic.generated.h"
/**
 * 
 */
UCLASS()
class IUNIUS_API UDash_Basic : public USkillBase
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, Category = "Dash")
	FVector DirectionDash;

	UPROPERTY(EditAnywhere, Category = "Dash")
		float SpeedDash = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "Dash")
		float DurationDash = 0.10f;

public:
	virtual void AfterSpawnActor() override;

	virtual void TickSkill(float DeltaSecond) override;

	virtual void EndExecute() override;

	virtual uint8 CanBeExecuted() override;

	UFUNCTION(BlueprintCallable)
	void SetDirectionDash(const FVector & Direction) { DirectionDash = Direction; }

};
