// Fill out your copyright notice in the Description page of Project Settings.

#include "DunceptionGameInstance.h"
#include "MoviePlayer.h"
#include "Engine/World.h"

void UDunceptionGameInstance::Init() 
{
	Super::Init();
	
	UE_LOG(LogTemp, Warning, TEXT("Fucking shitasdasd"));
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UDunceptionGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDunceptionGameInstance::EndLoadingScreen);
}

void UDunceptionGameInstance::BeginLoadingScreen(const FString& MapName) 
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	UE_LOG(LogTemp, Warning, TEXT("End Loading Screen"));
}

void UDunceptionGameInstance::EndLoadingScreen(UWorld* InLoadedWorld) 
{
	UE_LOG(LogTemp, Warning, TEXT("Babus"));
}