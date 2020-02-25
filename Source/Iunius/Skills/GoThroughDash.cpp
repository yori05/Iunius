// Fill out your copyright notice in the Description page of Project Settings.


#include "GoThroughDash.h"
#include "Components/SkillManagerComponent.h"
#include "IuniusCharacter.h"

void UGoThroughDash::AfterSpawnActor()
{
	Super::AfterSpawnActor();
	
	if (pTarget)
	{
		pTarget->SetCollisionProfileName(TEXT("DashOverlap"));
	}
}

void UGoThroughDash::EndExecute()
{
	Super::EndExecute();

	if (pTarget)
	{
		pTarget->SetCollisionProfileName(TEXT("DashOverlap"));
	}
}
