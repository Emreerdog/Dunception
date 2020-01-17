// Fill out your copyright notice in the Description page of Project Settings.

#include "FireSword.h"
#include "Components/PointLightComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFireSword::AFireSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FireSword = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FireSword"));
	FireSword->SetupAttachment(RootComponent);
	FireSword->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/SkeletalMeshes/Weapons/Swords/sword.sword'"), NULL, LOAD_None, NULL));
	
	FireSwordHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FireSwordHitbox"));
	FireSwordHitBox->SetupAttachment(FireSword);
	FireSwordHitBox->bHiddenInGame = false;
	FireSwordHitBox->RelativeScale3D = FVector(0.25f, 0.125f, 1.5f);
	FireSwordHitBox->RelativeLocation = FVector(0.0f, 0.0f, 90.0f);

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

// Called when the game starts or when spawned
void AFireSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

