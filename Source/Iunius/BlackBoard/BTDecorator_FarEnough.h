// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_FarEnough.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UBTDecorator_FarEnough : public UBTDecorator
{
	GENERATED_BODY()
	
protected :
	//Return if the distance with MyPawn & MyTarget > MyRange
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		struct FBlackboardKeySelector TargetPointerKey;

	UPROPERTY(EditAnywhere, Category = "Distance")
		float AcceptanceRadius = 150.0f;
};
