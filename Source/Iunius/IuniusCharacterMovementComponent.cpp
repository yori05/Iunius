// Fill out your copyright notice in the Description page of Project Settings.


#include "IuniusCharacterMovementComponent.h"
#include "GameFramework/Character.h"

uint8 UIuniusCharacterMovementComponent::GetCustomMode() const
{
	return CustomMovementMode;
}

bool UIuniusCharacterMovementComponent::IsDashing() const
{
	return (MovementMode == MOVE_Custom) && (CustomMovementMode == (uint8)EMovementModeCustom::CUSTOM_Dash) && UpdatedComponent;
}

void UIuniusCharacterMovementComponent::Dash(const FVector & DirectionToDash)
{
	if (!IsDashing())
	{
		SetMovementMode(MOVE_Custom, (uint8)EMovementModeCustom::CUSTOM_Dash);
		if (DirectionToDash.SizeSquared() > 0.0001f)
			DirectionDash = CharacterOwner->GetActorForwardVector();
		else
			DirectionDash = DirectionToDash;

		DashTimer = DashDuration;
		bOrientRotationToMovement = false;
	}
}

void UIuniusCharacterMovementComponent::StopDash()
{
	if (IsDashing())
	{
		SetMovementMode(MOVE_Walking, (uint8)EMovementModeCustom::CUSTOM_None);
		bOrientRotationToMovement = true;
	}
}

bool UIuniusCharacterMovementComponent::CanDash(FHitResult& resultHit) const
{
	return !IsDashing();
}

void UIuniusCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations) 
{
	Super::PhysCustom(deltaTime, Iterations);

	switch ((EMovementModeCustom) CustomMovementMode)
	{
	case EMovementModeCustom::CUSTOM_None:
		break;
	case EMovementModeCustom::CUSTOM_Dash:
		PhysDash(deltaTime, Iterations);
		break;
	case EMovementModeCustom::CUSTOM_Max:
		break;
	default:
		break;
	}
}

void UIuniusCharacterMovementComponent::PhysDash(float deltaTime, int32 Iterations)
{
	if (DashTimer < 0.0f)
		StopDash();

	DashTimer -= deltaTime;
	FHitResult hit;
	const auto Adjusted = DirectionDash * deltaTime * SpeedDash;
	SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentRotation(), true, hit);
}
