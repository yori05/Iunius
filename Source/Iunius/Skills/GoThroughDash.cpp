// Fill out your copyright notice in the Description page of Project Settings.


#include "GoThroughDash.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"
#include "Components/CapsuleComponent.h"

void UGoThroughDash::Initialize()
{
	Super::Initialize();
	CharacterCollider = pOwner->GetCharacterOwner()->GetCapsuleComponent();
}

void UGoThroughDash::FinishExecute()
{
	if (CharacterCollider)
	{
		CharacterCollider->SetCollisionProfileName(TEXT("DashOverlap"));
	}

	Super::FinishExecute();
}

void UGoThroughDash::EndExecute()
{
	Super::EndExecute();

	if (CharacterCollider)
	{
		CharacterCollider->SetCollisionProfileName(TEXT("Pawn"));
	}
}
