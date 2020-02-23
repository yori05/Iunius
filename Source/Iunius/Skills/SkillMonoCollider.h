// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillMonoActorBase.h"
#include "Engine/EngineTypes.h"
#include "SkillMonoCollider.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API USkillMonoCollider : public USkillMonoActorBase
{
	GENERATED_BODY()
	
protected:
	virtual void Execute() override;

	void ExecuteHandle();

public:
	virtual void DetectionMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillActorMeshCollider> CollisionDetection;
};
