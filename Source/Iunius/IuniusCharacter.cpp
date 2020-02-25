// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IuniusCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/IuniusCharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/SkillManagerComponent.h"
#include "Components/HealthComponent.h"

AIuniusCharacter::AIuniusCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIuniusCharacterMovementComponent>(AIuniusCharacter::CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	CustomCharacterMC = Cast<UIuniusCharacterMovementComponent>(GetCharacterMovement());

	//CharacterMovementComponent = Cast<UCharacterMovementComponent>()
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	//PerceptionComponent->ConfigureSense()

	SkillManagerComponent = CreateDefaultSubobject<USkillManagerComponent>("SkillManager");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AIuniusCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AIuniusCharacter::SkillDash(const FVector & DirectionToDash)
{
	if (SkillManagerComponent)
	{
		SkillManagerComponent->DashRequested(DirectionToDash);
	}
}

void AIuniusCharacter::MovementDash(const FVector& DirectionToDash, float Duration, float Speed)
{
	if (CustomCharacterMC)
	{
		CustomCharacterMC->Dash(DirectionToDash, Duration, Speed);
	}
}

uint8 AIuniusCharacter::CanMovementDash()
{
	return (CustomCharacterMC) ? CustomCharacterMC->CanDash() : 0;
}

void AIuniusCharacter::SetCollisionProfileName(FName ChannelColision)
{
	auto caps = GetCapsuleComponent();

	if (caps)
	{
		caps->SetCollisionProfileName(ChannelColision);
	}
}

uint8 AIuniusCharacter::IsDashing()
{
	return (CustomCharacterMC) ? CustomCharacterMC->IsDashing() : 0;
}


/*
void ATDTopDownCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto contrl = GetController();
	auto world = GetWorld();

	if (contrl != nullptr && world != nullptr)
	{
		if (MoveThisFrame > 0)
		{
			auto navSys = UNavigationSystemV1::GetNavigationSystem(world);
			if (MoveThisFrame == 2)
				MovementVectorThisFrame.Normalize();
			if (navSys != nullptr)
			{
				auto Destination = GetActorLocation() + MovementVectorThisFrame * MoveSpeed * DeltaSeconds;
				Destination = navSys->ProjectPointToNavigation(world, Destination);
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(contrl, Destination);
				//
				//if (Destination.SizeSquared() > 0.f)
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Destination => X : %f Y : %f Z : %f"), Destination.X,Destination.Y,Destination.Z));
				//

			}
		}

		auto acontrl = Cast<APlayerController>(contrl);

		if (acontrl != nullptr)
		{
			FHitResult TraceHitResult;
			acontrl->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			auto direction = TraceHitResult.ImpactPoint - GetActorLocation();
			if (direction.SizeSquared() > 0.1f)
			{
				direction.Z = 0;
				auto temp = (direction).ToOrientationRotator();
				SetActorRotation(temp);
			}
		}
	}

	MovementVectorThisFrame = FVector::ZeroVector;
	MoveThisFrame = false;
}

*/