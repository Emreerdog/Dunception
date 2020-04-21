// Fill out your copyright notice in the Description page of Project Settings.

#include "FireSword.h"
#include "Components/PointLightComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"
#include "HAL/FileManager.h"
#include "EnemyCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DefaultCharacter.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFireSword::AFireSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	const FString& ContentDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::GameContentDir());
	const FString& Type = "SkeletalMesh";
	const FString& MeshDir = "SkeletalMeshes/Weapons/Swords/sword.sword";
	const FString& LastDir = "SkeletalMesh'/Game/SkeletalMeshes/Weapons/Swords/sword.sword'";

	UE_LOG(LogTemp, Warning, TEXT("%s"), *LastDir);

	FireSword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FireSword"));
	FireSword->SetupAttachment(RootComponent);
	FireSword->SetSkeletalMesh(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *LastDir)));

	W_HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	W_HitBox->bHiddenInGame = true;
	W_HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	W_HitBox->RelativeScale3D = FVector(1.25f, 3.0f, 1.75f);
	W_HitBox->RelativeLocation = FVector(0.0f, 0.0f, 90.0f);
	W_HitBox->OnComponentBeginOverlap.AddDynamic(this, &AFireSword::OnWeaponOverlap);

	WeaponAttributes.Name = "FireSword";
	WeaponAttributes.Description = "Some strong thing";
	WeaponAttributes.Damage = 65.0f;
	WeaponAttributes.Price = 200.0f;

}

void AFireSword::FirstAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Some good shit"));
	bIsA1 = true;
}

void AFireSword::SecondAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("This is great"));
	bIsA2 = true;
}

void AFireSword::ThirdAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Working properly"));
	bIsA3 = false;
}

void AFireSword::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("SDFGSDGS"));
	AEnemyCharacter* tempEnemy = Cast<AEnemyCharacter>(OtherActor);
	if (tempEnemy) {
		bIsHitEnemy = true;
		bIsForcing = true;
		OwnerGuyYaw = OwnerGuy->GetActorRotation().Yaw;
		if (OwnerGuyYaw <= 0.0f) {
			GetWorldTimerManager().SetTimer(ForceTimer, this, &AFireSword::DeactivateForce, 0.10f);
			tempEnemy->DecreaseHealth(50.0f, true, FVector(0.0f, -130.0f, 0.0f), 0.1f);
		}
		else {
			GetWorldTimerManager().SetTimer(ForceTimer, this, &AFireSword::DeactivateForce, 0.10f);
			tempEnemy->DecreaseHealth(50.0f, true, FVector(0.0f, 130.0f, 0.0f), 0.1f);
		}
	}
	// DisableDamageBox();
	// W_HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFireSword::DeactivateForce()
{
	bIsForcing = false;
	bIsHitEnemy = false;
}

// Called when the game starts or when spawned
void AFireSword::BeginPlay()
{
	Super::BeginPlay();
	W_HitBox->DetachFromParent();
	OwnerGuy = Cast<ADefaultCharacter>(GetOwner());
}

// Called every frame
void AFireSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	W_HitBox->SetWorldLocation(OwnerGuy->DamageBoxLocation->GetComponentLocation());
	if (bIsForcing) {
		if (OwnerGuyYaw <= 0.0f) {
			OwnerGuy->GetCharacterMovement()->AddImpulse(FVector(0.0f, -35.0f, 0.0f));
		}
		else {
			OwnerGuy->GetCharacterMovement()->AddImpulse(FVector(0.0f, 35.0f, 0.0f));
		}
	}
}

