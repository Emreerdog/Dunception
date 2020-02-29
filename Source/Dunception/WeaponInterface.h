// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Interface.h"
#include "Components/BoxComponent.h"
#include "Array.h"
#include "WeaponInterface.generated.h"

class USkeletalMesh;
class UParticleSystemComponent;

USTRUCT()
struct DUNCEPTION_API FWeaponAttributes {
	GENERATED_BODY()

	// Those Attributes should be specified for each weapon in the game
	// To display them properly in the Weapon merchant and Inventory

	const char* Name; // Name of the weapon
	const char* Description; // It can be a story of a weapon or random bullshit
	float Damage = 0.0f; // Damage of weapon
	float Price = 0.0f; // Price of weapon
	const char* MeshPath; // Mesh of the weapon
	const char* VFXPath; // VFX like fire, ice etc.
	int ID;

};
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
	/*By the reason we have three attacks, every weapon should have attack functions specified*/

	virtual void FirstAttack() {

	}
	virtual void SecondAttack() {

	}
	virtual void ThirdAttack() {

	}

	/*Returns the attributes of a weapon that this interface is referencing at*/
	virtual FWeaponAttributes GetWeaponAttributes() {
		return WeaponAttributes;
	}

	virtual void SetAttributes(FWeaponAttributes NewAttributes);

	virtual void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {

	}

	/*Adding weapon to the weapon database*/
	static void AddWeaponToDB(IWeaponInterface* WeaponToAdd);

	/*Returns all the weapons that exists*/
	static TArray<IWeaponInterface*> GetAllWeapons();

	/*Searches the weapon by it's name and returns it*/
	static IWeaponInterface* GetWeaponByName(FString NameOfWeapon);

	/*Returns how many weapons we have*/
	static int GetWeaponCount();

protected:
	/*Weapon attribute structure for weapons*/
	FWeaponAttributes WeaponAttributes;
	UBoxComponent *W_HitBox;
private:
	static TArray<IWeaponInterface*> Weapons;
};