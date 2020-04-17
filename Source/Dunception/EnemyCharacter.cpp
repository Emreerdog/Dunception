// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "DunceptionGameModeBase.h"
#include "DefaultCharacter.h"
#include "DunceptionGameInstance.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
	GetCharacterMovement()->Mass = 2.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AEnemyCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

float AEnemyCharacter::GetHealth()
{
	return Health;
}

void AEnemyCharacter::DecreaseMovement(float DecreaseAmount, float TimeInSeconds)
{
	GetCharacterMovement()->MaxWalkSpeed -= DecreaseAmount;
	GetWorldTimerManager().SetTimer(MovementSlowTimer, this, &AEnemyCharacter::MovementToNormal, TimeInSeconds);
}

void AEnemyCharacter::DecreaseHealth(float DecreaseAmount, bool bImpulseOnImpact, FVector ImpulseDirection, float ImpulseTime)
{
	bIsImpulse = bImpulseOnImpact;
	ImpulseTimer = ImpulseTime;
	ImpulseDir = ImpulseDirection;
	Health -= DecreaseAmount;
}

void AEnemyCharacter::SetMass(float MassAmount)
{
	GetCharacterMovement()->Mass = MassAmount;
}

float AEnemyCharacter::GetMass()
{
	return GetCharacterMovement()->Mass;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();


	SetActorLocation(FVector(5.0f, GetActorLocation().Y, GetActorLocation().Z));
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsImpulse) 
	{
		Time += DeltaTime;
		if (Time >= ImpulseTimer) 
		{
			bIsImpulse = false;
			Time = 0.0f;
		}
		else {
			// UE_LOG(LogTemp, Warning, TEXT("Impulse working"));
			GetCharacterMovement()->AddImpulse(ImpulseDir);
		}
	}

	if (Health <= 0.0f) {
		static bool bIsDead;

		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		if (!bImpulse) {
			bImpulse = true;
			UDunceptionGameInstance* GameInst = Cast<UDunceptionGameInstance>(GetGameInstance());
			if (GameInst) {
				if (GameInst->GetDunceptionPlayer()) {
					ADefaultCharacter* tempOurGuy = Cast<ADefaultCharacter>(GameInst->GetDunceptionPlayer());
					if (tempOurGuy == nullptr) {
						UE_LOG(LogTemp, Warning, TEXT("Enemy doesn't see our guy"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("%s"), *tempOurGuy->GetActorLocation().ToString());
						if (tempOurGuy->GetActorRotation().Yaw < 0.0f) {
							UE_LOG(LogTemp, Warning, TEXT("FUCK MEEEEEE"));
							GetMesh()->AddImpulse(FVector(0.0f, -50000.0f, 1000.0f));
						}
						else {
							UE_LOG(LogTemp, Warning, TEXT("FUCK YOUUUUUUUUU"));
							GetMesh()->AddImpulse(FVector(0.0f, 50000.0f, 1000.0f));
						}
						// GetMesh()->AddRadialImpulse(tempOurGuy->GetMesh()->GetComponentLocation() + 50.0f, 1000.0f, 100000.0f, ERadialImpulseFalloff::RIF_Constant);
					}
				}
			}			
		}
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::MovementToNormal()
{
	GetWorldTimerManager().ClearTimer(MovementSlowTimer);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

