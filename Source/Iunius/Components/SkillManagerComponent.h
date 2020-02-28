// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManagerComponent.generated.h"

class AIuniusCharacter;
class USkillBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillMngrIntDelegate, const int32, SkillIndex);

UCLASS( ClassGroup=(Skill), meta=(BlueprintSpawnableComponent) )
class IUNIUS_API USkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Instanced)
	TArray<USkillBase*> Skills;
	AIuniusCharacter *pOwnerCharacter;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UFUNCTION(BlueprintCallable)
	AIuniusCharacter* GetCharacterOwner() { return pOwnerCharacter; }

	UFUNCTION(BlueprintCallable)
		uint8 IsASkillExecuting();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FSkillMngrIntDelegate onSkillRequested;

	//Call the delegate just in case the skill is launched
	UFUNCTION(BlueprintCallable)
		uint8 SkillRequested(const int32 SkillIndex);

	UFUNCTION(BlueprintCallable)
		uint8 DashRequested(const FVector & DirectionDash);

	UFUNCTION(BlueprintCallable)
		uint8 AttackRequested(const FVector& DirectionAttack);

	UFUNCTION(BlueprintCallable)
	USkillBase* GetDashSkill();
};
