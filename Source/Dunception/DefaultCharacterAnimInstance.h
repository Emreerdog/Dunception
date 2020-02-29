// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class DUNCEPTION_API UDefaultCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsOnAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bRunToIdleAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bSideMovementPressed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
	bool bIsWeaponWielded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
	TArray<bool> bAttackStates;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
		bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
		bool bIsOnSequence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
		bool bIsA1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
		bool bIsA2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat state")
		bool bIsA3;

private:
	AActor* OwnerActor;
	USkeletalMeshComponent* OwnerMesh;
};
