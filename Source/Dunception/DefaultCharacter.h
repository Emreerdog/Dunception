// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CameraAttributes.h"
#include "AMainHUD.h"
#include "CombatStates.h"
#include "MovementStates.h"
#include "WeaponInterface.h"
#include "DefaultCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UBoxComponent;
class IWeaponInterface;
class AFireSword;

UCLASS(BlueprintType)
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

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* RightHand;

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* DamageBoxLocation;

	// Class that manipulates springarm and camera and make them to do something(Camera shake, zoom out/in, etc.)
	CameraAttributes CameraHandler;

	// Class that contains the initial states of our character like is it moving, are we flying, etc.
	MovementStates movementStates;

	// Class that contains the initial combat states of our character like is weapon wielded, which attack type we are applying
	UPROPERTY(BlueprintReadWrite)
	FCombatStates combatStates;

	UPROPERTY(BlueprintReadOnly)
		AAMainHUD* MHUD;

	AFireSword* mSword;
	IWeaponInterface* WeaponHolder;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetIsOverlappingWithMerchant(bool MerchantOverlap);

	UFUNCTION()
		bool IsOverlappingWithMerchant();

	UFUNCTION()
		bool IsInteractionPressed();

	UFUNCTION(BlueprintImplementableEvent)
		void WooshSound();

	UFUNCTION(BlueprintImplementableEvent)
		void ArmorHitSound();

	UFUNCTION(Category = "DefaultCharacter effection functions", BlueprintCallable)
		float GetHealth();

	UFUNCTION(Category = "DefaultCharacter effection functions", BlueprintCallable)
		void DecreaseHealth(float DecreaseAmount);

	UFUNCTION(Category = "DefaultCharacter effection functions", BlueprintCallable)
		void SetHealth(float NewHealth);

	UFUNCTION(Category = "DefaultCharacter effection functions", BlueprintCallable)
		void DecreaseMovement(float DecreaseAmount, float TimeInSeconds);

private:
	// Side movement of character
	UFUNCTION()
		void SideMovement(float Value);

	UFUNCTION()
		void Run();

	UFUNCTION()
		void StopRun();

	// Z movement of character
	UFUNCTION()
		void _Jump();

	UFUNCTION()
		void MovementToNormal();

	UFUNCTION()
		void BasicAttack();

	UFUNCTION()
		void AttackMoment();

	UFUNCTION()
		void SecondAttack();

	UFUNCTION()
		void ThirdAttack();

	UFUNCTION()
		void ComboToBase();

	UFUNCTION()
		void BackToFirstAttack();

	UFUNCTION()
		void StopBasicAttack();

	UFUNCTION()
		void AttacksToDefault();

	UFUNCTION()
		void WeaponWield();

	UFUNCTION()
		void UnWieldTheWeapon();

	UFUNCTION()
		void WieldTheWeapon();

	UFUNCTION()
		void OpeningPanel();

	UFUNCTION()
		void ClosingPanel();

	UFUNCTION()
		void InteractionPressed();

	float MovementPushedTime;
	float WieldDelay;
	FTimerHandle WieldDelayTimerHandle;
	FTimerHandle ComboTimer;
	FTimerHandle AttackMomentTimer;
	FTimerHandle ComboToBaseTimer;
	FTimerHandle MovementSlowTimer;
	bool bIsMerchantOverlap;
	bool bIsInteractionPressed;
	float Health;

};
