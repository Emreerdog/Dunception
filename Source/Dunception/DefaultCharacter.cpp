// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacter.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	// We dont want spring arm to rotate with our player that would look weird
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 600.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SideMovement", this, &ADefaultCharacter::SideMovement);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::_Jump);
}

void ADefaultCharacter::SideMovement(float Value)
{
	if ((Controller != NULL) && Value != 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("SideMovement Executed"));
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ADefaultCharacter::_Jump()
{
	GetCharacterMovement()->bForceNextFloorCheck = true;
	bPressedJump = true;
	UE_LOG(LogTemp, Warning, TEXT("Jump Executed"));
}

