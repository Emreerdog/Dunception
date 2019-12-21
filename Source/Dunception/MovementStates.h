// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNCEPTION_API MovementStates
{
public:
	MovementStates();
	~MovementStates();

	float _Velocity = 0.0f; // As you see our velocity
	bool bIsOnAir = false; // It will be true when character is on air
	bool bRunToIdleAnim = false; // It will be true when character's velocity equal or more than 600 for 1.5 seconds
	bool bSideMovementPressed = false; // It'll be true when the movement key is pressed
	bool bIsRunning = false;
	bool bIsWeaponWielded = false;

private:

};
