// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Dash_Basic.h"
#include "Dash_GoThrough.generated.h"

/**
 * 
 */
UCLASS()
class IUNIUS_API UDash_GoThrough : public UDash_Basic
{
	GENERATED_BODY()
	
protected :
	virtual void AfterSpawnActor() override;
	virtual void EndExecute() override;

};
