// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IuniusAIController.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API AIuniusAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Controller")
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, Category = "Controller")
	class UBlackboardData* BBAsset;

	UPROPERTY(EditAnywhere, Category = "Controller")
	class UBlackboardComponent *CurrentBB;

	virtual void BeginPlay()override;

};
