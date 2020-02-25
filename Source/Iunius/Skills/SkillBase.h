// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "SkillBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkillDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillFloatDelegate, float, DeltaSecond);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillBoolDelegate, bool, SuccessFullRequest);

class USkillManagerComponent;
class ASkillActor;
class AIuniusCharacter;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInLineNew)
class IUNIUS_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onInitialize;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillFloatDelegate onTick;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onExecuted;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onEndExecution;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillBoolDelegate onRequestExecuted;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FComponentBeginOverlapSignature OnSkillActorBeginOverlap;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FComponentEndOverlapSignature OnSkillActorEndOverlap;

protected:
	UPROPERTY(VisibleAnywhere)
		USkillManagerComponent* pOwner = nullptr;

	UPROPERTY(VisibleAnywhere)
		ASkillActor* pActor = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkillActor> TypeOfSkillActor = nullptr;

	UPROPERTY(EditAnywhere)
		AIuniusCharacter* pTarget = nullptr;

	UPROPERTY(EditAnywhere)
		float Cooldown = 0.0f;

	UPROPERTY(VisibleAnywhere)
		float CooldownTimer = 0.0f;

	UPROPERTY(VisibleAnywhere)
		uint8 bIsExecuted = 0;

	UPROPERTY(EditAnywhere)
		uint8 bKillActorEndExecute = 1;

	UPROPERTY(EditAnywhere)
		uint8 bLinkActorToTarget = 1;

	UPROPERTY(EditAnywhere)
		uint8 bIsLocker = 0; //Set if this skill lock other skill when he is executed;

protected:
	UFUNCTION(BlueprintCallable)
		virtual void BeforeSpawnActor();

	UFUNCTION(BlueprintCallable)
		virtual void HalfWaySpawnActor();

	UFUNCTION(BlueprintCallable)
		virtual void AfterSpawnActor();

public:
	UFUNCTION(BlueprintCallable)
		virtual void Initialize(USkillManagerComponent* _Owner);

	UFUNCTION(BlueprintCallable)
		virtual void TickSkill(float DeltaSecond);

	UFUNCTION(BlueprintCallable)
		virtual void Execute();

	UFUNCTION(BlueprintCallable)
		virtual void EndExecute();

	UFUNCTION(BlueprintCallable)
		virtual uint8 RequestExecute();

	UFUNCTION(BlueprintCallable)
		uint8 IsExecuted() { return bIsExecuted; }

	UFUNCTION(BlueprintCallable)
		void LaunchRecuperation() { CooldownTimer = Cooldown; }

	UFUNCTION(BlueprintCallable)
		virtual uint8 CanBeExecuted() { return pOwner && !(CooldownTimer > 0 || bIsExecuted); }

	UFUNCTION(BlueprintCallable)
		uint8 IsLocked() { return (bIsLocker) ? bIsExecuted : bIsLocker; }

	UFUNCTION(BlueprintCallable)
		virtual void DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintCallable)
		ASkillActor* GetSkillActor() { return pActor; }

	UFUNCTION(BlueprintCallable)
		AIuniusCharacter* GetTarget() { return pTarget; }

	UFUNCTION(BlueprintCallable)
		void SetTarget(AIuniusCharacter* Target) { pTarget = Target; }

	UFUNCTION(BlueprintCallable)
		USkillManagerComponent* GetSkillManager() { return pOwner; }

	UFUNCTION(BlueprintCallable)
		void SetSkillManager(USkillManagerComponent* _Owner) { pOwner = _Owner; }

};
