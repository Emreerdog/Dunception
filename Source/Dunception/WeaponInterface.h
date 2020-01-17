// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Interface.h"
#include "WeaponInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class DUNCEPTION_API UWeaponInterface : public UInterface{
	GENERATED_BODY()

public:
	
};

class DUNCEPTION_API IWeaponInterface {
	GENERATED_BODY()

public:
	
	virtual void FirstAttack() {

	}
	virtual void SecondAttack() {

	}
	virtual void ThirdAttack() {

	}

};
