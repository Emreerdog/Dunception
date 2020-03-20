// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultCharacter.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DunceptionGameInstance.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "FireSword.h"
#include "Components/SkeletalMeshComponent.h"
#include "AMainHUD.h"
#include "GameFramework/PlayerController.h"
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
	SpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	RightHand = CreateDefaultSubobject<USceneComponent>(TEXT("RightHand"));
	RightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponPocket"));
	RightHand->SetRelativeLocation(FVector(-0.618f, -36.840001f, 3.030949f));
	RightHand->SetRelativeRotation(FRotator(-9.800f, -1.75f, -259.8f));

	CameraHandler.SetSpringArmAndCamera(SpringArm, Camera);

	DamageBoxLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DamageBoxLocation"));
	DamageBoxLocation->SetupAttachment(GetMesh());

	Health = 100.0f;

	// GetController()->CastToPlayerController()->GetHUD()->Destroy();
	// GetController()->CastToPlayerController()->ClientSetHUD(AAMainHUD::StaticClass());
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = false;
	SpawnParameters.Instigator = NULL;
	SpawnParameters.Owner = this;

	mSword = GetWorld()->SpawnActor<AFireSword>(SpawnParameters);
	mSword->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetIncludingScale);

	WeaponHolder = mSword;

	MHUD = Cast<AAMainHUD>(GetController()->CastToPlayerController()->GetHUD());

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

	if (GetCharacterMovement()->IsFalling()) {
		movementStates.bIsOnAir = true;
	}
	else {
		movementStates.bIsOnAir = false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%d%d%d%d%d"), combatStates.bIsBasicAttack, combatStates.bIsOnSequence, combatStates.bIsA1, combatStates.bIsA2, combatStates.bIsA3);
	// UE_LOG(LogTemp, Warning, TEXT("Movement State: %d\nRun to Stop anim prepared: %d\nVelocity: %f"), movementStates.bSideMovementPressed, movementStates.bRunToIdleAnim, movementStates._Velocity);
	// UE_LOG(LogTemp, Warning, TEXT("%f"), GetWorldTimerManager().GetTimerRemaining(ComboTimer));
	// UE_LOG(LogTemp, Warning, TEXT("%f"), GetCharacterMovement()->Mass);
	if (Health <= 0.0f) {
		DisableInput(GetController()->CastToPlayerController());
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		WeaponHolder->DisableDamageBox();
	}
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
	PlayerInputComponent->BindAction("BasicAttack", IE_Pressed, this, &ADefaultCharacter::BasicAttack);
	PlayerInputComponent->BindAction("BasicAttack", IE_Released, this, &ADefaultCharacter::StopBasicAttack);
	PlayerInputComponent->BindAction("OpenControlPanel", IE_Pressed, this, &ADefaultCharacter::OpeningPanel);
	PlayerInputComponent->BindAction("OpenControlPanel", IE_Released, this, &ADefaultCharacter::ClosingPanel);
	PlayerInputComponent->BindAction("InteractWithThings", IE_Pressed, this, &ADefaultCharacter::InteractionPressed);

}

void ADefaultCharacter::SetIsOverlappingWithMerchant(bool MerchantOverlap)
{
	this->bIsMerchantOverlap = MerchantOverlap;
}

// Function that moves character right or left
void ADefaultCharacter::SideMovement(float Value)
{
	if ((Controller != NULL) && Value != 0.0f) {
		if (movementStates.bAbleToMove) {
			// Because of our game is 3D side scroller, movement event will only be happening on Z-Y axis
			// Thats we put movement only on Y-axis
			AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);

			// It counts how long we push the movement keys such as (A,S)
			MovementPushedTime += GetWorld()->DeltaTimeSeconds;
			movementStates.bSideMovementPressed = true;
			if (Value > 0.0f) {
				// TODO Camera Lag
			}
			else {
				
			}
		}
	}
	else {
		// If we don't push the movement keys exactly below events will happen
		MovementPushedTime = 0.0f;
		movementStates.bSideMovementPressed = false;		
	}
}

void ADefaultCharacter::Run()
{
	// Checking if the weapon interface and weapon we have is not a nullptr
	
	if (mSword) {
		
	}

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
	if (movementStates.bAbleToMove) {
		bPressedJump = true;
		UE_LOG(LogTemp, Warning, TEXT("Jump Executed"));
	}
}

void ADefaultCharacter::BasicAttack()
{
	if (combatStates.bIsWeaponWielded) 
	{
		combatStates.bIsBasicAttack = true;
		combatStates.bIsBasicAttackForAnim = true;
		if ((!combatStates.bIsA2) && (!combatStates.bIsA3)) 
		{
			if (!combatStates.bIsA1) 
			{
				combatStates.bIsOnSequence = true;
				movementStates.bAbleToMove = false;
				combatStates.bIsA1 = true;
				WeaponHolder->FirstAttack();
				GetWorldTimerManager().SetTimer(AttackMomentTimer, this, &ADefaultCharacter::AttackMoment, 0.45f);
				GetWorldTimerManager().SetTimer(ComboTimer, this, &ADefaultCharacter::SecondAttack, 0.9f);
				combatStates.bIsBasicAttack = false;
			}
		}
	}
}

void ADefaultCharacter::AttackMoment()
{
	WooshSound();
	GetWorldTimerManager().ClearTimer(AttackMomentTimer);
	WeaponHolder->EnableDamageBox();
	WeaponHolder->DisableDamageBox();
	if (WeaponHolder->IsHitEnemy()) {
		ArmorHitSound();
	}
}

void ADefaultCharacter::SecondAttack() 
{
	GetWorldTimerManager().ClearTimer(ComboTimer);
	if ((combatStates.bIsBasicAttack && combatStates.bIsOnSequence) && combatStates.bIsA1) {
		WeaponHolder->SecondAttack();
		combatStates.bIsA2 = true;
		GetWorldTimerManager().SetTimer(AttackMomentTimer, this, &ADefaultCharacter::AttackMoment, 0.65f);
		GetWorldTimerManager().SetTimer(ComboTimer, this, &ADefaultCharacter::ThirdAttack, 1.0f);
		combatStates.bIsBasicAttack = false;
	}
	else {
		GetWorldTimerManager().SetTimer(ComboToBaseTimer, this, &ADefaultCharacter::ComboToBase, 0.15f);
	}
}

void ADefaultCharacter::ThirdAttack() 
{
	GetWorldTimerManager().ClearTimer(ComboTimer);
	if ((combatStates.bIsBasicAttack && combatStates.bIsOnSequence) && (combatStates.bIsA1 && combatStates.bIsA2)) {
		combatStates.bIsA3 = true;
		WeaponHolder->ThirdAttack();
		GetWorldTimerManager().SetTimer(AttackMomentTimer, this, &ADefaultCharacter::AttackMoment, 0.70f);
		GetWorldTimerManager().SetTimer(ComboTimer, this, &ADefaultCharacter::BackToFirstAttack, 1.2f);
	}
	else {
		GetWorldTimerManager().SetTimer(ComboToBaseTimer, this, &ADefaultCharacter::ComboToBase, 0.65f);
	}
}

void ADefaultCharacter::ComboToBase()
{
	GetWorldTimerManager().ClearTimer(ComboToBaseTimer);
	movementStates.bAbleToMove = true;
	AttacksToDefault();
}

void ADefaultCharacter::BackToFirstAttack()
{
	GetWorldTimerManager().ClearTimer(ComboTimer);
	if (combatStates.bIsBasicAttack) {
		AttacksToDefault();
		BasicAttack();
	}
	else {
		GetWorldTimerManager().SetTimer(ComboToBaseTimer, this, &ADefaultCharacter::ComboToBase, 0.9f);
	}
	//if (combatStates.bIsBasicAttack) {
	//	// If three of the attacks are zero it means that we were at idle state
	//	if ((!combatStates.AttackStates[0] && !combatStates.AttackStates[1]) && !combatStates.AttackStates[2]) {
	//		// Make first attack true
	//		combatStates.AttackStates[0] = true;
	//	}
	//	if (combatStates.AttackStates[0]) {
	//		combatStates.AttackTimer += GetWorld()->DeltaTimeSeconds;
	//		float Result = combatStates.AttackAnimLength[0] - combatStates.AttackTimer;
	//		// UE_LOG(LogTemp, Warning, TEXT("Attack1:%d AttackTimer:%f Result:%f %f"), combatStates.AttackStates[0], combatStates.AttackTimer, Result, combatStates.PreparingTime);
	//		if ((Result <= 0.2f)) {
	//			combatStates.PreparingTime += GetWorld()->DeltaTimeSeconds;
	//			if (combatStates.PreparingTime >= 0.19f) {
	//				UE_LOG(LogTemp, Warning, TEXT("Attack1:%d AttackTimer:%f Result:%f %f"), combatStates.AttackStates[0], combatStates.AttackTimer, Result, combatStates.PreparingTime);
	//				combatStates.AttackStates[0] = false;
	//				combatStates.AttackStates[1] = true;
	//				combatStates.AttackTimer = 0.0f;
	//				combatStates.PreparingTime = 0.0f;
	//				UE_LOG(LogTemp, Warning, TEXT("Attack1:%d AttackTimer:%f Result:%f %f"), combatStates.AttackStates[0], combatStates.AttackTimer, Result, combatStates.PreparingTime);
	//			}
	//		}
	//	}
	//	else if (combatStates.AttackStates[1]) {
	//		UE_LOG(LogTemp, Warning, TEXT("LOL"));

	//		combatStates.AttackTimer += GetWorld()->DeltaTimeSeconds;
	//		float Result = combatStates.AttackAnimLength[0] - combatStates.AttackTimer;
	//		if ((Result <= 0.2f)) {

	//		}
	//	}
	//	else if (combatStates.AttackStates[2]) {

	//	}
	//}	
}

void ADefaultCharacter::StopBasicAttack()
{
	if (GetWorldTimerManager().GetTimerRemaining(ComboTimer) <= 0.2f) {
		combatStates.bIsBasicAttack = true;
		combatStates.bIsBasicAttackForAnim = true;
	}
	else {
		combatStates.bIsBasicAttack = false;
		combatStates.bIsBasicAttackForAnim = false;
	}
}

void ADefaultCharacter::AttacksToDefault()
{
	combatStates.bIsBasicAttack = false;
	combatStates.bIsOnSequence = false;
	combatStates.bIsA1 = false;
	combatStates.bIsA2 = false;
	combatStates.bIsA3 = false;
	combatStates.bIsBasicAttackForAnim = false;
}

void ADefaultCharacter::WeaponWield()
{
	if (!combatStates.bIsWeaponWielded) {
		combatStates.bIsWeaponWielded = true;
		GetWorldTimerManager().SetTimer(WieldDelayTimerHandle, this, &ADefaultCharacter::WieldTheWeapon, 0.8f / 2);
	}
	else {
		combatStates.bIsWeaponWielded = false;
		GetWorldTimerManager().SetTimer(WieldDelayTimerHandle, this, &ADefaultCharacter::UnWieldTheWeapon, 0.8f / 2);
	}
}

void ADefaultCharacter::UnWieldTheWeapon()
{
	GetWorldTimerManager().ClearTimer(WieldDelayTimerHandle);
	RightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponPocket"));
	RightHand->SetRelativeLocation(FVector(-0.618f, -36.840001f, 3.030949f));
	RightHand->SetRelativeRotation(FRotator(-9.800f, -1.75f, -259.8f));
}

void ADefaultCharacter::WieldTheWeapon()
{
	GetWorldTimerManager().ClearTimer(WieldDelayTimerHandle);
	RightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));
	RightHand->SetRelativeLocation(FVector(-0.01f, 3.34f, -15.8f));
	RightHand->SetRelativeRotation(FRotator(18.9f, -12.4f, -11.1));
}

void ADefaultCharacter::OpeningPanel()
{
	MHUD->EnablePanel();
}

void ADefaultCharacter::ClosingPanel()
{
	MHUD->DisablePanel();
}

void ADefaultCharacter::InteractionPressed()
{
	bIsInteractionPressed = true;
}

bool ADefaultCharacter::IsOverlappingWithMerchant()
{
	return bIsMerchantOverlap;
}

bool ADefaultCharacter::IsInteractionPressed()
{
	return bIsInteractionPressed;
}

float ADefaultCharacter::GetHealth()
{
	return Health;
}

void ADefaultCharacter::DecreaseHealth(float DecreaseAmount)
{
	Health -= DecreaseAmount;
}

void ADefaultCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

