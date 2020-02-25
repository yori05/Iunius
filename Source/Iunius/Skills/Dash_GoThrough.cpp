// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash_GoThrough.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"

void UDash_GoThrough::AfterSpawnActor()
{
	Super::AfterSpawnActor();
	
	if (pTarget)
	{
		pTarget->SetCollisionProfileName(TEXT("DashOverlap"));
	}
}

void UDash_GoThrough::EndExecute()
{
	Super::EndExecute();

	if (pTarget)
	{
		pTarget->SetCollisionProfileName(TEXT("Pawn"));
	}
}
