// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "FireSword.generated.h"

class USkeletalMeshComponent;
class UPointLightComponent;
class UBoxComponent;
class ADefaultCharacter;

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

	UFUNCTION()
	virtual void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* FireSword;

	UFUNCTION()
		void DeactivateForce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ADefaultCharacter* OwnerGuy;
	FTimerHandle ForceTimer;
	bool bIsForcing = false;
};
