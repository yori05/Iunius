// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "SkillActors/SkillActor.h"
#include "SkillMonoActorBase.generated.h"

class ASkillActor;

/**
 * 
 */
UCLASS()
class IUNIUS_API USkillMonoActorBase : public USkillBase
{
	GENERATED_BODY()
protected :
		UPROPERTY(VisibleAnywhere)
		ASkillActor *pActor = nullptr;

		UPROPERTY(EditAnywhere)
			TSubclassOf<ASkillActor> TypeOfSkillActor;

public :
	UFUNCTION(BlueprintCallable)
	ASkillActor *GetSkillActor() { return pActor; }

};
