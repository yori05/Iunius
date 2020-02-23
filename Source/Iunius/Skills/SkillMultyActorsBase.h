// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "SkillActors/SkillActor.h"
#include "SkillMultyActorsBase.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API USkillMultyActorsBase : public USkillBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		TArray<ASkillActor*> pActors;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASkillActor> TypeOfSkillActor;

public:
	UFUNCTION(BlueprintCallable)
		TArray<ASkillActor*> GetSkillActors() { return pActors; }

};
