// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class USpringArmComponent;
class USkeletalMeshComponent;
class UBoxComponent;

UCLASS(BlueprintType)
class DUNCEPTION_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(BlueprintCallable)
		void SetHealth(float NewHealth); // Different from decreasehealth

	UFUNCTION(BlueprintCallable)
		float GetHealth();

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	UFUNCTION()
		void DecreaseHealth(float DecreaseAmount, bool bImpulseOnImpact = false, FVector ImpulseDirection = FVector::ZeroVector, float ImpulseTime = 0.0f);
=======
=======
>>>>>>> 580fb23d5d1bf6e6e0cb22745077f5dc9d4fe1b3
=======
>>>>>>> 580fb23d5d1bf6e6e0cb22745077f5dc9d4fe1b3
	UFUNCTION(BlueprintCallable)
		void DecreaseHealth(float DecreaseAmount);
>>>>>>> 580fb23d5d1bf6e6e0cb22745077f5dc9d4fe1b3

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float Health = 100.0f;
	float ImpulseTimer = 0.0f;
	float Time = 0.0f;;
	bool bIsImpulse = false;
	FVector ImpulseDir = FVector::ZeroVector;
};
