// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AgroCheck.h"
#include "IuniusAIController.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

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
		TArray<AActor> outActor;
		/*
		TEnumAsByte<EObjectTypeQuery> ObjectToTrace = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(ObjectToTrace);

		TArray<AActor> ActorsToIgnore;

		ActorsToIgnore.Add(Cast<AActor>(MyPawn));
		UKismetSystemLibrary::SphereOverlapActors(World, pawnLocation, rangeDetection, );
		*/
	}
}

void UBTService_AgroCheck::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}
