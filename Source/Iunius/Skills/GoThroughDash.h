// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/BasicDash.h"
#include "GoThroughDash.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UGoThroughDash : public UBasicDash
{
	GENERATED_BODY()
	
protected :
	virtual void AfterSpawnActor() override;
	virtual void EndExecute() override;

};
