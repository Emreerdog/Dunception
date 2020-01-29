// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WeaponInterface.h"
#include "MainMapState.generated.h"

/**
 * 
 */
UCLASS()
class DUNCEPTION_API AMainMapState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMainMapState(const FObjectInitializer& ObjectInitializer);
	TArray<FWeaponAttributes> AllWeapons;

private:

};
