// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DunceptionGameModeBase.generated.h"

class ADefaultCharacter;
class AAMainHUD;

/**
 * 
 */
UCLASS()
class DUNCEPTION_API ADunceptionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADunceptionGameModeBase(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
