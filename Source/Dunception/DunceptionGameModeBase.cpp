// Fill out your copyright notice in the Description page of Project Settings.

#include "DunceptionGameModeBase.h"
#include "ConstructorHelpers.h"

ADunceptionGameModeBase::ADunceptionGameModeBase(const FObjectInitializer& ObjectInitializer) 
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacter(TEXT("Pawn '/Game/BluePrints/DefaultCharacter_BP/DefaultCharacter.DefaultCharacter_C'"));

	if (DefaultCharacter.Class != NULL) {
		DefaultPawnClass = DefaultCharacter.Class;
		UE_LOG(LogTemp, Warning, TEXT("DefaultCharacter possesed %s"), *DefaultPawnClass->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("DefaultCharacter couldn't possesed"));
	}
}

