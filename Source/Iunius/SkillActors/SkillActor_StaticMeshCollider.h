// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActors/SkillActor_PrimitiveCollider.h"
#include "SkillActor_StaticMeshCollider.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API ASkillActor_StaticMeshCollider : public ASkillActor_PrimitiveCollider
{
	GENERATED_BODY()
	
public :
	ASkillActor_StaticMeshCollider();

};
