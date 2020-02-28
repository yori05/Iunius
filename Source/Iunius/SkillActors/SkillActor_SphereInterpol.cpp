// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_SphereInterpol.h"
#include "Components/InterpToMovementComponent.h"

ASkillActor_SphereInterpol::ASkillActor_SphereInterpol()
{
	InterpTMComponent = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovementComponent");

	if (InterpTMComponent && RootComponent)
	{
		InterpTMComponent->SetUpdatedComponent(RootComponent);
		//InterpTMComponent->RestartMovement()
	}
}
