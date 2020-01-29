// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMerchant.h"
#include "Components/SkeletalMeshComponent.h"
#include "DefaultCharacter.h"
#include "MainMapState.h"
#include "WeaponInterface.h"
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

	Row = 0;
	Coloumn = 0;

}

// Called when the game starts or when spawned
void AWeaponMerchant::BeginPlay()
{
	Super::BeginPlay();
	
	MerchantInteractionArea->OnComponentBeginOverlap.AddDynamic(this, &AWeaponMerchant::EnableMerchantPanel);
	MerchantInteractionArea->OnComponentEndOverlap.AddDynamic(this, &AWeaponMerchant::DisableMerchantPanel);

	MainMapState = Cast<AMainMapState>(GetWorld()->GetGameState());

	if (MainMapState) {
		for (int i = 0; i < MainMapState->AllWeapons.Num(); i++) {
			WeaponID = MainMapState->AllWeapons[i].ID;
			WeaponDamage = MainMapState->AllWeapons[i].Damage;
			WeaponDescription = MainMapState->AllWeapons[i].Description;
			WeaponName = MainMapState->AllWeapons[i].Name;
			WeaponCost = MainMapState->AllWeapons[i].Price;

			AssignWeaponRowsAndColoumns();
			Coloumn++;
			if (Coloumn == 4) {
				Row++;
				Coloumn = 0;
			}
			bIsAssignmentFinished = true;
		}
	}

}

// Called every frame
void AWeaponMerchant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainMapState) {
		// UE_LOG(LogTemp, Warning, TEXT("%d"), MainMapState->AllWeapons.Num());
	}

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

