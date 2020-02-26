// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Dash_GoThrough.h"
#include "Dash_Overlap.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FDetectionOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);

/**
 * 
 */
UCLASS()
class IUNIUS_API UDash_Overlap : public UDash_GoThrough
{
	GENERATED_BODY()
	
protected :

	virtual void HalfWaySpawnActor() override;

	virtual void DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
