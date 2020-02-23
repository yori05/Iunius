// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_FarEnough.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_FarEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AcceptanceRadius <= 0.f)
		return true;

	auto AiController = Cast<AAIController>(OwnerComp.GetOwner());
	auto BBComp = OwnerComp.GetBlackboardComponent();
	if (AiController &&  BBComp)
	{
		auto Target = Cast<AActor>(BBComp->GetValueAsObject(TargetPointerKey.SelectedKeyName));
		auto MyPawn = AiController->GetPawn();

		if (Target && MyPawn)
		{
			float distance = (Target->GetActorLocation() - MyPawn->GetActorLocation()).SizeSquared();

			if (distance > (AcceptanceRadius * AcceptanceRadius))
				return true;
		}
	}

	return false;
}

