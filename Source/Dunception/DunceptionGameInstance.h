// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DunceptionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNCEPTION_API UDunceptionGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
		FVector2D GetGameViewPortSize();

	UPROPERTY(BlueprintReadWrite)
		int WeaponID;

	UPROPERTY(BlueprintReadWrite)
		float WeaponDamage;

	UPROPERTY(BlueprintReadWrite)
		FString WeaponName;

	UPROPERTY(BlueprintReadWrite)
		FString WeaponDescription;

	UPROPERTY(BlueprintReadWrite)
		float WeaponCost;

};
