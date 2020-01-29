// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMapState.h"

AMainMapState::AMainMapState(const FObjectInitializer& ObjectInitializer) 
{
	FWeaponAttributes Weapons[6];
	Weapons[0].Damage = 50.0f;
	Weapons[0].Description = "Ozanin evinden gelen sekil bir balta";
	Weapons[0].ID = 10001;
	Weapons[0].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_AnthraciteAxe/SK_Blade_AnthraciteAxe.SK_Blade_AnthraciteAxe'";
	Weapons[0].Name = "Antracite Axe";
	Weapons[0].Price = 15.0f;

	Weapons[1].Damage = 165.0f;
	Weapons[1].Description = "Anilin low baltasi";
	Weapons[1].ID = 10002;
	Weapons[1].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_BohntaPick/SK_Blade_BohntaPick.SK_Blade_BohntaPick'";
	Weapons[1].Name = "Bohnta Pick";
	Weapons[1].Price = 80.0f;

	Weapons[2].Damage = 500.0f;
	Weapons[2].Description = "Mustafanin OP baltasi";
	Weapons[2].ID = 10003;
	Weapons[2].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_CrudeAxe/SK_Blade_CrudeAxe.SK_Blade_CrudeAxe'";
	Weapons[2].Name = "Crude Axe";
	Weapons[2].Price = 650.0f;

	Weapons[3].Damage = 20.0f;
	Weapons[3].Description = "Tunanin veled baltasi";
	Weapons[3].ID = 10004;
	Weapons[3].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_DeadlyAxe/SK_Blade_DeadlyAxe.SK_Blade_DeadlyAxe'";
	Weapons[3].Name = "Deadly Axe";
	Weapons[3].Price = 2.0f;

	Weapons[4].Damage = 10.0f;
	Weapons[4].Description = "Alpturkun saci";
	Weapons[4].ID = 10005;
	Weapons[4].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_ExecutionerAxe/SK_Blade__ExecutionerAxe.SK_Blade__ExecutionerAxe'";
	Weapons[4].Name = "Executioner Axe";
	Weapons[4].Price = 5.0f;

	Weapons[5].Damage = 1.0f;
	Weapons[5].Description = "Barisin mistleri";
	Weapons[5].ID = 10006;
	Weapons[5].MeshPath = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_FissureBlade/SK_Blade_FissureBlade.SK_Blade_FissureBlade'";
	Weapons[5].Name = "Fissure Axe";
	Weapons[5].Price = 0.5f;

	for (int i = 0; i < sizeof(Weapons) / sizeof(FWeaponAttributes); i++) {
		AllWeapons.Add(Weapons[i]);
	}

}
