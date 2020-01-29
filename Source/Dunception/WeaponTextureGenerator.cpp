// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponTextureGenerator.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponTextureGenerator::AWeaponTextureGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetupAttachment(RootComponent);

	WeaponScene = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Scene"));
	WeaponScene->SetupAttachment(SceneRoot);
	WeaponScene->RelativeLocation = FVector(0.0f, -15.0f, -17.0f);
	WeaponScene->RelativeRotation = FRotator(00.0f, 0.0f, 40.0f);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(WeaponScene);

	SceneCaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Camera"));
	SceneCaptureCamera->SetupAttachment(RootComponent);
	SceneCaptureCamera->RelativeLocation = FVector(-80.0f, 10.0f, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("ASFA"));

}

// Called when the game starts or when spawned
void AWeaponTextureGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponTextureGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

