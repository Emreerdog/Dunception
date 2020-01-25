// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMerchant.h"
#include "Components/SkeletalMeshComponent.h"
#include "DefaultCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeaponMerchant::AWeaponMerchant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MerchantMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MerchantMesh"));
	MerchantMesh->SetupAttachment(RootComponent);

	MerchantInteractionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionArea"));
	MerchantInteractionArea->AttachToComponent(MerchantMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	MerchantInteractionArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Called when the game starts or when spawned
void AWeaponMerchant::BeginPlay()
{
	Super::BeginPlay();
	
	MerchantInteractionArea->OnComponentBeginOverlap.AddDynamic(this, &AWeaponMerchant::EnableMerchantPanel);
	MerchantInteractionArea->OnComponentEndOverlap.AddDynamic(this, &AWeaponMerchant::DisableMerchantPanel);

}

// Called every frame
void AWeaponMerchant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OverlappedGuy) {
		bIsCharacterInteracting = OverlappedGuy->IsInteractionPressed();
	}
	else {
		bIsCharacterInteracting = false;
	}
}

void AWeaponMerchant::EnableMerchantPanel(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->IsA<ADefaultCharacter>()) {
		UE_LOG(LogTemp, Warning, TEXT("Baba"));
		OverlappedGuy = Cast<ADefaultCharacter>(OtherActor);
		if (OverlappedGuy) {
			OverlappedGuy->SetIsOverlappingWithMerchant(true);
			bIsCharacterOverlapping = OverlappedGuy->IsOverlappingWithMerchant();
		}
	}
}

void AWeaponMerchant::DisableMerchantPanel(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->IsA<ADefaultCharacter>()) {
		UE_LOG(LogTemp, Warning, TEXT("Anan"));
		OverlappedGuy = Cast<ADefaultCharacter>(OtherActor);
		if (OverlappedGuy) {
			OverlappedGuy->SetIsOverlappingWithMerchant(false);
			bIsCharacterOverlapping = OverlappedGuy->IsOverlappingWithMerchant();
			OverlappedGuy = nullptr;
		}
	}
}

