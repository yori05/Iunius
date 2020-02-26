// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Dash_GoThrough.h"
#include "Dash_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UDash_Projectile : public UDash_GoThrough
{
	GENERATED_BODY()

protected :
	UPROPERTY(BlueprintReadOnly, Category = "MainData")
	ASkillActor* pActorProjectile = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ASkillActor> TypeOfSkillProjectileActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float SpeedProjectile = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float TimeLifeProjectile = 3.f;

public :
	virtual void HalfWaySpawnActor() override;

	virtual void AfterSpawnActor() override;

	virtual void DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
