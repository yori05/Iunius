// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "SkillMovementBase.generated.h"

class UIuniusCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class IUNIUS_API USkillMovementBase : public USkillBase
{
	GENERATED_BODY()
	
protected :

	UIuniusCharacterMovementComponent *pMovementComponent;

public :
	void SetMovementComponent(UIuniusCharacterMovementComponent * MovementComponent) {
		pMovementComponent = MovementComponent;
	};

};
