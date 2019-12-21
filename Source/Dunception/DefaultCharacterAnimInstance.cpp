// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"
#include "DefaultCharacter.h"

void UDefaultCharacterAnimInstance::NativeInitializeAnimation() 
{
	OwnerActor = GetOwningActor();
	if (!OwnerActor) {
		if (ADefaultCharacter* ActorOwner = Cast<ADefaultCharacter>(OwnerActor)) {
			UE_LOG(LogTemp, Warning, TEXT("Casting to %s is succesfull"), *ActorOwner->GetName());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Character couldn't owned"));
		}
	}
}

void UDefaultCharacterAnimInstance::NativeBeginPlay()
{
}

void UDefaultCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Checking character's states every frame and sending variables to the animation blueprint
	// Those variables will be used on animation execution logic
	if (OwnerActor) {
		ADefaultCharacter* m_Character = Cast<ADefaultCharacter>(OwnerActor);
		if (m_Character) {
			Velocity = m_Character->movementStates._Velocity;
			bIsOnAir = m_Character->movementStates.bIsOnAir;
			bSideMovementPressed = m_Character->movementStates.bSideMovementPressed;
			bRunToIdleAnim = m_Character->movementStates.bRunToIdleAnim;
			bIsRunning = m_Character->movementStates.bIsRunning;
			bIsWeaponWielded = m_Character->movementStates.bIsWeaponWielded;
		}
	}
}
