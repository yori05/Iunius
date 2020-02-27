// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_BoxHealer.h"
#include "Components/HealerComponent.h"

ASkillActor_BoxHealer::ASkillActor_BoxHealer()
{
	HealerComponent = CreateDefaultSubobject<UHealerComponent>("HealerComponent");
}
