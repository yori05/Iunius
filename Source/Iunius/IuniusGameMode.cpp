// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IuniusGameMode.h"
#include "IuniusPlayerController.h"
#include "IuniusCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AIuniusGameMode::AIuniusGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AIuniusPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/IuniusCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


}

void AIuniusGameMode::LoadDynamicLevel()
{
}
