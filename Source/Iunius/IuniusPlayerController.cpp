// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IuniusPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "IuniusCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

AIuniusPlayerController::AIuniusPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bWantToDash = false;
}

void AIuniusPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MovementVectorThisFrame.Normalize();

	DirectionCursor = MyPawn->GetCursorToWorld()->GetComponentLocation() - MyPawn->GetActorLocation();
	DirectionCursor.Z = 0;

	if (DirectionCursor.IsNearlyZero())
	{
		DirectionCursor = MyPawn->GetActorForwardVector();
	}

	DirectionCursor.Normalize();

	if (MyPawn->GetCanUseSkill())
	{
		if (bWantToDash)
		{
			bWantToDash = false;
			MyPawn->SkillDash(DirectionCursor);
		}
		if (bWantToAttack)
		{
			bWantToAttack = false;
			MyPawn->SkillAttack(DirectionCursor);
		}
	}
	if (MyPawn->GetCanRotate())
	{
		auto temp = (DirectionCursor).ToOrientationRotator();
		MyPawn->SetActorRotation(temp);
	}
	if (MyPawn->GetCanMove())
	{
		// keep updating the destination every tick while desired
		if (MovementVectorThisFrame.SizeSquared() > 0.0f)
		{
			MoveFromMovementVector(DeltaTime);
		}
	}

	MovementVectorThisFrame = FVector::ZeroVector;
}


void AIuniusPlayerController::SetPawn(APawn* InPaw)
{
	Super::SetPawn(InPaw);

	MyPawn = Cast<AIuniusCharacter>(InPaw);

}

void AIuniusPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AIuniusPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AIuniusPlayerController::MoveRight);

	InputComponent->BindAction("Dash", IE_Pressed, this, &AIuniusPlayerController::Dash);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AIuniusPlayerController::Attack);

}

void AIuniusPlayerController::MoveForward(float _value)
{
	MovementVectorThisFrame.X += _value;
}

void AIuniusPlayerController::MoveRight(float _value)
{
	MovementVectorThisFrame.Y += _value;
}

void AIuniusPlayerController::MoveFromMovementVector(float DeltaTime)
{
	auto world = GetWorld();

	if (MyPawn && world)
	{
		auto navSys = UNavigationSystemV1::GetNavigationSystem(world);
		if (navSys != nullptr)
		{
			auto Destination = MyPawn->GetActorLocation() + MovementVectorThisFrame * 10000.0f * DeltaTime;
			Destination = navSys->ProjectPointToNavigation(world, Destination);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
		}
	}
}

void AIuniusPlayerController::Dash()
{
	bWantToDash = true;
}

void AIuniusPlayerController::Attack()
{
	bWantToAttack = true;
}
