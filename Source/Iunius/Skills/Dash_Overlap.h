// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/GoThroughDash.h"
#include "Dash_Overlap.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FDetectionOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);

/**
 * 
 */
UCLASS()
class IUNIUS_API UDash_Overlap : public UGoThroughDash
{
	GENERATED_BODY()
	
protected :

public :
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDetectionOverlap Event_OnDetectionOverlap;
};
