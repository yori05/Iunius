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
}

void AIuniusPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	if (MovementVectorThisFrame.SizeSquared() > 0.0f)
	{
		MoveFromMovementVector(DeltaTime);
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

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AIuniusPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AIuniusPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AIuniusPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AIuniusPlayerController::MoveToTouchLocation);

	InputComponent->BindAxis("MoveForward", this, &AIuniusPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AIuniusPlayerController::MoveRight);
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
	MovementVectorThisFrame.Normalize();
	auto world = GetWorld();

	if (MyPawn && world)
	{
		auto navSys = UNavigationSystemV1::GetNavigationSystem(world);
		if (navSys != nullptr)
		{
			auto Destination = MyPawn->GetActorLocation() + MovementVectorThisFrame * 10000.0f * DeltaTime;
			Destination = navSys->ProjectPointToNavigation(world, Destination);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
			
			
			//if (GEngine)
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Destination => X : %f Y : %f Z : %f"), Destination.X,Destination.Y,Destination.Z));
		}
	}

	/*
	if (MyPawn)
	{
		FHitResult TraceHitResult;
		GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		auto direction = TraceHitResult.ImpactPoint - MyPawn->GetActorLocation();
		if (direction.SizeSquared() > 0.1f)
		{
			direction.Z = 0;
			auto temp = (direction).ToOrientationRotator();
			MyPawn->SetActorRotation(temp);
		}
	}
	*/
}

void AIuniusPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (MyPawn)
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AIuniusPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AIuniusPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	//APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AIuniusPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AIuniusPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
