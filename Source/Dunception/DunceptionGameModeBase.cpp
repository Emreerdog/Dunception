// Fill out your copyright notice in the Description page of Project Settings.

#include "DunceptionGameModeBase.h"
#include "AMainHUD.h"
#include "DefaultCharacter.h"
#include "ConstructorHelpers.h"

ADunceptionGameModeBase::ADunceptionGameModeBase(const FObjectInitializer& ObjectInitializer) 
{

	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacter(TEXT("Pawn '/Game/BluePrints/DefaultCharacter_BP/DefaultCharacter.DefaultCharacter_C'"));
	static ConstructorHelpers::FClassFinder<AAMainHUD> MainHUD(TEXT("HUD'/Script/Dunception.AMainHUD'"));

	if (MainHUD.Class) {
		HUDClass = MainHUD.Class;
	}

	if (DefaultCharacter.Class != NULL) {
		DefaultPawnClass = DefaultCharacter.Class;
		UE_LOG(LogTemp, Warning, TEXT("DefaultCharacter possesed %s"), *DefaultPawnClass->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("DefaultCharacter couldn't possesed"));
	}
}

void ADunceptionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("FUCK"));
}


void ADunceptionGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
