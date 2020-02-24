// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActors/SkillActor_PrimitiveCollider.h"
#include "SkillActor_CapsuleCollider.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API ASkillActor_CapsuleCollider : public ASkillActor_PrimitiveCollider
{
	GENERATED_BODY()
	
public :
	ASkillActor_CapsuleCollider();
};
