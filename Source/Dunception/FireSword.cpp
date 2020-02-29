// Fill out your copyright notice in the Description page of Project Settings.

#include "FireSword.h"
#include "Components/PointLightComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"
#include "HAL/FileManager.h"
#include "EnemyCharacter.h"
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

	W_HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FireSwordHitbox"));
	W_HitBox->SetupAttachment(FireSword);
	W_HitBox->bHiddenInGame = false;
	W_HitBox->RelativeScale3D = FVector(0.25f, 0.125f, 1.5f);
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
	if (GetOwner()) {
		UE_LOG(LogTemp, Error, TEXT("%s"), *GetOwner()->GetName());
	}
}

void AFireSword::SecondAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("This is great"));
}

void AFireSword::ThirdAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Working properly"));
}

void AFireSword::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemyCharacter>()) {
		AEnemyCharacter* tempEnemy = Cast<AEnemyCharacter>(OtherActor);
		if (tempEnemy) 
		{
			tempEnemy->DecreaseHealth(WeaponAttributes.Damage);
		}
	}
	else {
		// Nothing
	}
}

// Called when the game starts or when spawned
void AFireSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//if (ADefaultCharacter* TempDefault = Cast<ADefaultCharacter>(GetOwner())) {
	//	if (TempDefault->combatStates.bIsBasicAttack) {
	//		UE_LOG(LogTemp, Warning, TEXT("Forcing"));
	//		TempDefault->GetCharacterMovement()->AddImpulse(FVector(0.0f, 1000.0f, 0.0f));
	//	}
	//}
}

