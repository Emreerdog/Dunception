// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatStates.h"

FCombatStates::FCombatStates()
{
	
}

FCombatStates::~FCombatStates()
{
}

void FCombatStates::AttacksToDefault()
{
	bIsWeaponWielded = false; 
	bIsBasicAttack = false; 
	bIsOnSequence = false;
	bIsBasicAttackForAnim = false;
	bIsA1 = false;
	bIsA2 = false;
	bIsA3 = false;
	AttackTimer = 0.0f; 
	PreparingTime = 0.0f;
}
