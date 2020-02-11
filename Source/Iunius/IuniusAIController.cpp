// Fill out your copyright notice in the Description page of Project Settings.


#include "IuniusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void AIuniusAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTAsset)
		RunBehaviorTree(BTAsset);

	if (BBAsset)
		UseBlackboard(BBAsset, CurrentBB);
}