// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(BlueprintType)
enum class EDamageResult : uint8
{
	DamageResult_None UMETA(DisplayName = "None"),
	DamageResult_Absorbed UMETA(DisplayName = "Absorbed"),
	DamageResult_Imune UMETA(DisplayName = "Imune"),
	DamageResult_Deal  UMETA(DisplayName = "Deal"),
	DamageResult_Kill  UMETA(DisplayName = "Kill"),
	DamageResult_Max  UMETA(Hidden),
};

UENUM(BlueprintType)
enum class EDamageElement : uint8
{
	DamageResult_None UMETA(DisplayName = "None"),
	DamageResult_Neutral UMETA(DisplayName = "Neutral"),
	DamageResult_Fire  UMETA(DisplayName = "Fire"),
	DamageResult_Wind  UMETA(DisplayName = "Wind"),
	DamageResult_Water  UMETA(DisplayName = "Fire"),
	DamageResult_Earth  UMETA(DisplayName = "Earth"),
	DamageResult_Energy  UMETA(DisplayName = "Energy"),
	DamageResult_Light  UMETA(DisplayName = "Light"),
	DamageResult_Shadow  UMETA(DisplayName = "Shadow"),
	DamageResult_Wild  UMETA(DisplayName = "Wild"),
	DamageResult_Max  UMETA(Hidden),
};
