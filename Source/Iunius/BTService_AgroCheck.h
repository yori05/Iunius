// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "GameFramework/Actor.h"
#include "BTService_AgroCheck.generated.h"

/**
 *	Behavior Tree service nodes is designed to perform "background" tasks that update AI's knowledge.
 *
 *  Services are being executed when underlying branch of behavior tree becomes active,
 *  but unlike tasks they don't return any results and can't directly affect execution flow.
 *
 *  Usually they perform periodical checks (see TickNode) and often store results in blackboard.
 *  If any decorator node below requires results of check beforehand, use OnSearchStart function.
 *   Keep in mind that any checks performed there have to be instantaneous!
 *
 *  Other typical use case is creating a marker when specific branch is being executed
 *  (see OnBecomeRelevant, OnCeaseRelevant), by setting a flag in blackboard.
 *
 *  Because some of them can be instanced for specific AI, following virtual functions are not marked as const:
 *   - OnBecomeRelevant (from UBTAuxiliaryNode)
 *   - OnCeaseRelevant (from UBTAuxiliaryNode)
 *   - TickNode (from UBTAuxiliaryNode)
 *   - OnSearchStart
 *
 *  If your node is not being instanced (default behavior), DO NOT change any properties of object within those functions!
 *  Template nodes are shared across all behavior tree components using the same tree asset and must store
 *  their runtime properties in provided NodeMemory block (allocation size determined by GetInstanceMemorySize() )
 */
UCLASS()
class IUNIUS_API UBTService_AgroCheck : public UBTService
{
	GENERATED_BODY()
	
public :
	UBTService_AgroCheck();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> TypeofTarget;

	UPROPERTY(EditAnywhere)
		float rangeDetection = 1500.0f;

protected :
	UPROPERTY(EditAnywhere)
	class AIuniusAIController *MyAIController = nullptr;

	virtual void SetOwner(AActor* ActorOwner) override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
