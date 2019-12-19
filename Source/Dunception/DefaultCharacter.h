// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DUNCEPTION_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

	// That is a SpringArm in which our camera will be attached to (It is like selfie stick)
	UPROPERTY(EditDefaultsOnly)
		USpringArmComponent* SpringArm;

	// Our Camera as we see
	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* Camera;

	UPROPERTY()
		float _Velocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Side movement of character
	UFUNCTION()
		void SideMovement(float Value);

	// Z movement of character
	UFUNCTION()
		void _Jump();
};
