// Fill out your copyright notice in the Description page of Project Settings.


#include "IuniusCharacterMovementComponent.h"

/*
void UIuniusCharacterMovementComponent::OnMovementModeChanged(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	if (!HasValidData())
	{
		return;
	}

	Super::OnMovementModeChanged(NewMovementMode, NewCustomMode);


}
*/

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
		DirectionDash = DirectionToDash;
		DashTimer = DashDuration;
	}
}

bool UIuniusCharacterMovementComponent::CanDash(FHitResult& resultHit) const
{
	return false;
}
