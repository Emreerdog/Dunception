// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacter.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
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
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 600.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f); // ...at this rotation rate

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponPocket"));
	Weapon->SetRelativeLocation(FVector(-0.618f, -36.840001f, 3.030949f));
	Weapon->SetRelativeRotation(FRotator(-9.800f, -1.75f, -259.8f));

	CameraHandler.SetSpringArmAndCamera(SpringArm, Camera);
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

	movementStates._Velocity = GetVelocity().Y;

	// If we move on +Y axis our velocity will be 600 but it is -600 on -Y axis
	// We are doing this to make our Velocity always positive
	if (movementStates._Velocity < 0) {
		movementStates._Velocity = -movementStates._Velocity;
	}

	if (MovementPushedTime >= 0.5f) {
		movementStates.bRunToIdleAnim = true;
	}
	else {
		movementStates.bRunToIdleAnim = false;
	}

	if (GetCharacterMovement()->IsFalling()) {
		movementStates.bIsOnAir = true;
	}
	else {
		movementStates.bIsOnAir = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Movement State: %d\nRun to Stop anim prepared: %d\nVelocity: %f"), movementStates.bSideMovementPressed, movementStates.bRunToIdleAnim, movementStates._Velocity);
}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("WieldWeapon", IE_Pressed, this, &ADefaultCharacter::WeaponWield);
	PlayerInputComponent->BindAxis("SideMovement", this, &ADefaultCharacter::SideMovement);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::_Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADefaultCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ADefaultCharacter::StopRun);

}

// Function that moves character right or left
void ADefaultCharacter::SideMovement(float Value)
{
	if ((Controller != NULL) && Value != 0.0f) {
		// Because of our game is 3D side scroller, movement event will only be happening on Z-Y axis
		// Thats we put movement only on Y-axis
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);

		// It counts how long we push the movement keys such as (A,S)
		MovementPushedTime += GetWorld()->DeltaTimeSeconds;
		movementStates.bSideMovementPressed = true;
		// UE_LOG(LogTemp, Warning, TEXT("%f"), MovementPushedTime);

	}
	else {
		// If we don't push the movement keys exactly below events will happen
		MovementPushedTime = 0.0f;
		movementStates.bSideMovementPressed = false;
	}
}

void ADefaultCharacter::Run()
{
	movementStates.bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 850.0f;
}

void ADefaultCharacter::StopRun()
{
	movementStates.bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ADefaultCharacter::_Jump()
{
	bPressedJump = true;
	UE_LOG(LogTemp, Warning, TEXT("Jump Executed"));
}

void ADefaultCharacter::WeaponWield()
{
	movementStates.bIsWeaponWielded = true;
	GetWorldTimerManager().SetTimer(WieldDelayTimerHandle, this, &ADefaultCharacter::WieldTheWeapon, 0.8f/2);
}

void ADefaultCharacter::WieldTheWeapon()
{
	GetWorldTimerManager().ClearTimer(WieldDelayTimerHandle);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));
	Weapon->SetRelativeLocation(FVector(-0.01f, 3.34f, -15.8f));
	Weapon->SetRelativeRotation(FRotator(18.9f, -12.4f, -11.1));
}

