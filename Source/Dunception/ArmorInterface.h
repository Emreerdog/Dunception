// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArmorInterface.generated.h"

USTRUCT()
struct DUNCEPTION_API FArmorAttributes {
	GENERATED_BODY()

		// Those Attributes should be specified for each armor in the game
		// To display them properly in the Armor merchant and Inventory

	const char* Name; // Name of the armor
	const char* Description; // It can be a story of a armor or random bullshit
	float DamageReduction = 0.0f; // Damage reduction
	float ConditionResistance = 0.0f; // Condition Resistance
	unsigned int Durability = 0;
	const char* MeshPath; // Mesh of the armor
	const char* VFXPath; // VFX like fire, ice etc.
	int ID;

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArmorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNCEPTION_API IArmorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnDamageTaken() {

	}

	virtual void OnCrowdControl() {

	}

	virtual void OnSlow() {

	}

	virtual void OnStun() {

	}

	FArmorAttributes GetAttributes() {
		return ArmorAttributes;
	}

	void SetArmorAttributes(FArmorAttributes NewAttributes);

protected:
	FArmorAttributes ArmorAttributes;

};
