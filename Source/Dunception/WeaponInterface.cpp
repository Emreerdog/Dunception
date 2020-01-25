// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponInterface.h"

TArray<IWeaponInterface*> IWeaponInterface::Weapons;

void IWeaponInterface::AddWeaponToDB(IWeaponInterface *WeaponToAdd)
{
	if (WeaponToAdd) {
		Weapons.Add(WeaponToAdd);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Weapon you want to add is not valid"));
	}
}

TArray<IWeaponInterface*> IWeaponInterface::GetAllWeapons()
{
	return Weapons;
}

IWeaponInterface * IWeaponInterface::GetWeaponByName(FString NameOfWeapon)
{
	return nullptr;
}

int IWeaponInterface::GetWeaponCount()
{
	return Weapons.Num();
}

void IWeaponInterface::SetAttributes(FWeaponAttributes NewAttributes)
{
	this->WeaponAttributes = NewAttributes;
}
