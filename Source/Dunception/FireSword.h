// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "FireSword.generated.h"

class USkeletalMeshComponent;
class UPointLightComponent;
class UBoxComponent;

UCLASS()
class DUNCEPTION_API AFireSword : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireSword();

	virtual void FirstAttack() override;
	virtual void SecondAttack() override;
	virtual void ThirdAttack() override;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* FireSword;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* FireSwordHitBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
};
