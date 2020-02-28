// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/SkillBase.h"
#include "Shot_Direction.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UShot_Direction : public USkillBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "MainData")
		TArray<ASkillActor*> pActors;

	UPROPERTY(EditAnywhere, Category = "Attack")
		uint8 ShotEject = 8;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float DurationAttack = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float SpeedProjectile = 2000.f;

protected:
	virtual void Execute() override;
	virtual void EndExecute() override;
	virtual void AfterSpawnActor() override;
	virtual void FDetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
