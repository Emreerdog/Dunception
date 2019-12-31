// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/SlateWrapperTypes.h"
#include "AMainHUD.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DUNCEPTION_API AAMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AAMainHUD();

	UPROPERTY(BlueprintReadOnly)
		ESlateVisibility ControlPanelVisibility;

	void EnablePanel();
	void DisablePanel();

};
