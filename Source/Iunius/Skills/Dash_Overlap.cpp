// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash_Overlap.h"
#include "SkillActors/SkillActor_CapsuleCollider.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"

void UDash_Overlap::FinishExecute()
{
	auto CapsuleActor = Cast<ASkillActor_CapsuleCollider>(pActor);
	if (CapsuleActor)
	{
		auto Collider = CapsuleActor->GetColliderComponent();
		if (Collider)
		{
			Collider->OnComponentBeginOverlap.AddDynamic(this, &UDash_Overlap::DetectionOverlap);
		}
	}

	Super::FinishExecute();
}

void UDash_Overlap::DetectionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!CharacterCollider || OtherActor != CharacterCollider->GetAttachmentRootActor())
	{
		Event_OnDetectionOverlap.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		if (GEngine && OtherActor)
		{
			GEngine->AddOnScreenDebugMessage(12, 2, FColor::White, FString("Collide avec un actor ! => ") + OtherActor->GetName());
		}
	}
}
