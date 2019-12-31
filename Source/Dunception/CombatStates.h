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
	TArray<bool> AttackStates; // Attack1, Attack2, Attack3

	UPROPERTY(BlueprintReadWrite)
	bool bIsWeaponWielded = false; // Did we equip the weapon ?

	UPROPERTY(BlueprintReadWrite)
	bool bIsBasicAttack = false; // Check if we are attacking

	UPROPERTY(BlueprintReadWrite)
	TArray<float> AttackAnimLength; // Animation lengths of attacks

	UPROPERTY(BlueprintReadWrite)
	float AttackTimer; // It will start counting from 0 to end of animation when we start attacking

	UPROPERTY(BlueprintReadWrite)
	float PreparingTime;

	void AttacksToDefault();
};
