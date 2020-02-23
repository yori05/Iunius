// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MoveToTarget.h"
#include "IuniusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTaskNode_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyController = Cast<AIuniusAIController>(OwnerComp.GetOwner());
	auto BBComp = OwnerComp.GetBlackboardComponent();
	if (MyController && BBComp)
	{
		AActor* CurrentTarget = Cast<AActor>(BBComp->GetValueAsObject(TargetPointerKey.SelectedKeyName));
		AActor* CurrentPawn = MyController->GetPawn();

		if (CurrentTarget && CurrentPawn)
		{
			auto result = MyController->MoveToActor(CurrentTarget, 100.0f);

			if (result == EPathFollowingRequestResult::Failed)
				return EBTNodeResult::InProgress; //InProgress : continue task
		}
	}

	return EBTNodeResult::Failed; //stop task
}
