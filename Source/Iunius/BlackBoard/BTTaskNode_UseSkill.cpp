// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_UseSkill.h"
#include "IuniusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IuniusCharacter.h"

EBTNodeResult::Type UBTTaskNode_UseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyController = Cast<AIuniusAIController>(OwnerComp.GetOwner());
	auto BBComp = OwnerComp.GetBlackboardComponent();
	if (MyController && BBComp)
	{
		auto CurrentPawn = Cast<AIuniusCharacter>(MyController->GetPawn());

		if (CurrentPawn)
		{
			if (SkillIndex == 0)
			{
				auto result = CurrentPawn->SkillDash(CurrentPawn->GetActorForwardVector());

				if (result)
					return EBTNodeResult::Succeeded; //InProgress : continue task
			}
			else if (SkillIndex == 1)
			{
				auto result = CurrentPawn->SkillAttack(CurrentPawn->GetActorForwardVector());

				if (result)
					return EBTNodeResult::Succeeded; //InProgress : continue task
			}
			else
			{
				auto result = CurrentPawn->UseSkill(SkillIndex);

				if (result)
					return EBTNodeResult::Succeeded; //InProgress : continue task
			}
		}
	}

	return EBTNodeResult::Failed; //stop task
}
