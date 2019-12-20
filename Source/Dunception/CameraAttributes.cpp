// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraAttributes.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

CameraAttributes::CameraAttributes()
{
}

CameraAttributes::~CameraAttributes()
{
}

void CameraAttributes::SetSpringArmAndCamera(USpringArmComponent * SArm, UCameraComponent * Cam)
{
	PlayerSpringArm = SArm;
	PlayerCamera = Cam;
}
