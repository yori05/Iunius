// Fill out your copyright notice in the Description page of Project Settings.


#include "IuniusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Classes//Engine/EngineTypes.h"
//#include "Engine/TimerManger.h"

void AIuniusAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTAsset)
		RunBehaviorTree(BTAsset);

	if (BBAsset)
		UseBlackboard(BBAsset, CurrentBB);

	auto MyPawn = Cast<AActor>(GetPawn());

	FTimerHandle ExecuteTimerHandle;
	GetWorldTimerManager().SetTimer(ExecuteTimerHandle, this, &AIuniusAIController::InitializeBlackBoardComponent, 0.1f);
}

void AIuniusAIController::InitializeBlackBoardComponent()
{
	auto MyPawn = Cast<AActor>(GetPawn());

	if (MyPawn)
	{
		CurrentBB->SetValueAsObject(PawnPointerKey.SelectedKeyName, MyPawn);
		CurrentBB->SetValueAsVector(PawnLocationKey.SelectedKeyName, MyPawn->GetActorLocation());
	}
}
