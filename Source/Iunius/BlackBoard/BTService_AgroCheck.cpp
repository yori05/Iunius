// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AgroCheck.h"
#include "IuniusAIController.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_AgroCheck::UBTService_AgroCheck() :
	Super()
{
	bNotifyCeaseRelevant = 1;
	bNotifyBecomeRelevant = 1;
}

void UBTService_AgroCheck::SetOwner(AActor* ActorOwner)
{
	MyAIController = Cast<AIuniusAIController>(ActorOwner);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Become Relevant !")));

}

void UBTService_AgroCheck::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp,NodeMemory);
	MyAIController = Cast<AIuniusAIController>(OwnerComp.GetOwner());

	/*
	if (MyAIController)
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Set AI Controller")));
			*/
}
void UBTService_AgroCheck::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}
void UBTService_AgroCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentBB = OwnerComp.GetBlackboardComponent();
	auto World = GetWorld();
	if (MyAIController && World)
	{
		auto MyPawn = MyAIController->GetPawn();
		auto pawnLocation = MyPawn->GetActorLocation();
		TArray<AActor*> outActor;
		
		TEnumAsByte<EObjectTypeQuery> ObjectToTrace = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(ObjectToTrace);

		TArray<AActor*> ActorsToIgnore;

		ActorsToIgnore.Add(Cast<AActor>(MyPawn));
		if (UKismetSystemLibrary::SphereOverlapActors(World, pawnLocation, rangeDetection, ObjectTypes, TypeofTarget, ActorsToIgnore, outActor))
		{
			
			FHitResult resultHit;
			FCollisionQueryParams queryParams;
			queryParams.AddIgnoredActors(ActorsToIgnore);

			for (auto i : outActor)
			{
				auto targetLocation = i->GetActorLocation();
				World->LineTraceSingleByChannel(resultHit, pawnLocation, targetLocation, ECollisionChannel::ECC_Camera,queryParams);

				if (resultHit.bBlockingHit && resultHit.Actor == i)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetPointerKey.SelectedKeyName, i);
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, targetLocation);
				}
				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetPointerKey.SelectedKeyName, nullptr);
				}
			}
		}
		
	}
}

void UBTService_AgroCheck::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}
