// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatStates.h"

FCombatStates::FCombatStates()
{
	AttackAnimLength.Add(1.48f); // Melee Attack Downward
	AttackAnimLength.Add(2.11f); // Melee Attack high 360
	AttackAnimLength.Add(1.55f); // Melee Attack 360 low
	AttackAnimLength.Add(2.08f);

	AttackStates.Add(0);
	AttackStates.Add(0);
	AttackStates.Add(0);

	bIsWeaponWielded = false;
	AttackTimer = 0.0f;
	bIsBasicAttack = false;
	PreparingTime = 0.0f;

}

FCombatStates::~FCombatStates()
{
}

void FCombatStates::AttacksToDefault()
{
	// AttackAnimLength[0] = 1.48f;
	// AttackAnimLength[1] = 2.11f;
	// AttackAnimLength[2] = 1.55f;
	// AttackAnimLength[3] = 2.08f;

	// AttackStates.Add(0);
	// AttackStates.Add(0);
	// AttackStates.Add(0);
}
