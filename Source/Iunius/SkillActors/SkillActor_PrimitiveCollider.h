// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActor.h"
#include "SkillActor_PrimitiveCollider.generated.h"

class UPrimitiveComponent;

/**
 * 
 */
UCLASS()
class IUNIUS_API ASkillActor_PrimitiveCollider : public ASkillActor
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* ColliderComponent;

public :
	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetColliderComponent() { return ColliderComponent; }

};
