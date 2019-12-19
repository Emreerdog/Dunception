// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacterAnimInstance.h"
#include "DefaultCharacter.h"

void UDefaultCharacterAnimInstance::NativeInitializeAnimation() 
{
	OwnerActor = GetOwningActor();
	if (!OwnerActor) {
		if (ADefaultCharacter* ActorOwner = Cast<ADefaultCharacter>(OwnerActor)) {
			Velocity = ActorOwner->_Velocity;
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
	if (OwnerActor) {
		ADefaultCharacter* m_Character = Cast<ADefaultCharacter>(OwnerActor);
		if (m_Character) {
			Velocity = m_Character->_Velocity;
		}
	}
}
