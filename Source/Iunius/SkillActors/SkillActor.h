// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "SkillActor.generated.h"

class USkillBase;
class USceneComponent;
class UDamagerComponent;

UCLASS()
class IUNIUS_API ASkillActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASkillActor();

public :
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FComponentBeginOverlapSignature OnColliderBeginOverlap;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FComponentEndOverlapSignature OnColliderEndOverlap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillBase* pSkillOwner;

	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* ColliderComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UDamagerComponent* DamagerComponent = nullptr;

public:	//Membre
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Init(USkillBase* SkillOwner);

	UFUNCTION(BlueprintCallable)
	void SetSkillOwner(USkillBase * SkillOwner) { pSkillOwner = SkillOwner; }

	UFUNCTION(BlueprintCallable)
	bool AttachRootToActor(USceneComponent* ComponentLinked);

	UFUNCTION(BlueprintCallable)
		virtual void DetectionColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void DetectionColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void DestroySkillActor();

public : //Accesseur
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UPrimitiveComponent* GetColliderComponent() { return ColliderComponent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UDamagerComponent* GetDamagerComponent() { return DamagerComponent; }

};
