// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkillDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillFloatDelegate, float, DeltaSecond);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillBoolDelegate, bool, SuccessFullRequest);

class USkillManagerComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInLineNew)
class IUNIUS_API USkillBase : public UObject
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere)
	uint8 bIsExecuted = 0;

	UPROPERTY(EditAnywhere)
		float Cooldown = 0.0f;

	UPROPERTY(VisibleAnywhere)
		float CooldownTimer = 0.0f;

	UPROPERTY(VisibleAnywhere)
		USkillManagerComponent *pOwner = nullptr;

	UPROPERTY(EditAnywhere)
		uint8 bIsLocker = 0; //Set if this skill lock other skill when he is executed;

public :

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onInitialize;
	UFUNCTION(BlueprintCallable)
		virtual void Initialize() { onInitialize.Broadcast(); }

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FSkillFloatDelegate onTick;

	UFUNCTION(BlueprintCallable)
	virtual void TickSkill(float DeltaSecond);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onExecuted;

	UFUNCTION(BlueprintCallable)
		virtual void Execute() { bIsExecuted = 1; onExecuted.Broadcast(); }

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillDelegate onEndExecution;
	UFUNCTION(BlueprintCallable)
		virtual void EndExecute() { bIsExecuted = 0; onEndExecution.Broadcast(); }
	

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FSkillBoolDelegate onRequestExecuted;

	UFUNCTION(BlueprintCallable)
		virtual uint8 RequestExecute() 
	{
		if (CanBeExecuted()) { onRequestExecuted.Broadcast(0); return 0; } Execute();  onRequestExecuted.Broadcast(1); return 1;
	}
	
	UFUNCTION(BlueprintCallable)
		bool IsExecuted() { return bIsExecuted; }

	UFUNCTION(BlueprintCallable)
		void LaunchRecuperation() { CooldownTimer = Cooldown; }

	UFUNCTION(BlueprintCallable)
		virtual uint8 CanBeExecuted() { return pOwner && !(CooldownTimer > 0 || bIsExecuted); }

	UFUNCTION(BlueprintCallable)
		void SetSkillManager(USkillManagerComponent *_Owner) { pOwner = _Owner; }

	UFUNCTION(BlueprintCallable)
		USkillManagerComponent* GetSkillManager() { return pOwner; }

	UFUNCTION(BlueprintCallable)
		bool IsLocked() { return (bIsLocker) ? bIsExecuted : bIsLocker; }
};
