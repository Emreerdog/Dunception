// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */

class DUNCEPTION_API CameraAttributes
{

public:
	CameraAttributes();
	~CameraAttributes();
	void SetSpringArmAndCamera(USpringArmComponent* SArm, UCameraComponent* Cam);

private:
	USpringArmComponent* PlayerSpringArm;
	UCameraComponent* PlayerCamera;
};
