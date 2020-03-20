// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectMacros.h"
#include "Components/SlateWrapperTypes.h"
#include "CombatStates.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNCEPTION_API FCombatStates
{

	GENERATED_BODY()

	FCombatStates();
	~FCombatStates();

	UPROPERTY(BlueprintReadWrite)
	bool bIsWeaponWielded = false; // Did we equip the weapon ?

	UPROPERTY(BlueprintReadWrite)
	bool bIsBasicAttack = false; // Check if we are attacking

	UPROPERTY(BlueprintReadWrite)
	bool bIsOnSequence = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsBasicAttackForAnim = false; // Don't ask me it is weirdly necessary

	UPROPERTY(BlueprintReadWrite)
	bool bIsA1 = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsA2 = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsA3 = false;

	UPROPERTY(BlueprintReadWrite)
	float AttackTimer; // It will start counting from 0 to end of animation when we start attacking

	UPROPERTY(BlueprintReadWrite)
	float PreparingTime;

	bool bAttackMomentA1 = false;
	bool bAttackMomentA2 = false;
	bool bAttackMomentA3 = false;

	void AttacksToDefault();
};
