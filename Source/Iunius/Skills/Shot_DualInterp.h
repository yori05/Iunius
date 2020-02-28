// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/SkillBase.h"
#include "Shot_DualInterp.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UShot_DualInterp : public USkillBase
{
	GENERATED_BODY()

protected :
	UPROPERTY(BlueprintReadOnly, Category = "MainData")
		ASkillActor* pActorSecondary = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
		float DurationAttack = 2.0f;

protected :
	virtual void Execute() override;
	virtual void EndExecute() override;
	virtual void AfterSpawnActor() override;
	virtual void FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
