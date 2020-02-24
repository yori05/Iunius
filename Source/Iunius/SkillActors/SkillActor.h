// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillActor.generated.h"

class USkillBase;
class USceneComponent;

UCLASS()
class IUNIUS_API ASkillActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASkillActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillBase* pSkillOwner;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Init(USkillBase* SkillOwner);

	UFUNCTION(BlueprintCallable)
	void SetSkillOwner(USkillBase * SkillOwner) { pSkillOwner = SkillOwner; }
	bool AttachRootToActor(USceneComponent * ParentComponent);
};
