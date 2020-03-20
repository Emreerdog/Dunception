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

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		void SetHealth(float NewHealth); // Different from decreasehealth

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		float GetHealth();

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		void DecreaseMovement(float DecreaseAmount, float Time);

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		void DecreaseHealth(float DecreaseAmount, bool bImpulseOnImpact = false, FVector ImpulseDirection = FVector::ZeroVector, float ImpulseTime = 0.0f);

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		void SetMass(float MassAmount);

	UFUNCTION(Category = "Enemy Effect Functions", BlueprintCallable)
		float GetMass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
		void MovementToNormal();

	float Health = 100.0f;
	float ImpulseTimer = 0.0f;
	float Time = 0.0f;;
	bool bIsImpulse = false;
	bool bImpulse = false;
	FVector ImpulseDir = FVector::ZeroVector;
	FTimerHandle MovementSlowTimer;
};
