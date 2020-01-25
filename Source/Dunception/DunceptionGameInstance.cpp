// Fill out your copyright notice in the Description page of Project Settings.

#include "DunceptionGameInstance.h"
#include "MoviePlayer.h"
#include "Misc/MessageDialog.h"
#include "HAL/FileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "FireSword.h"
#include "Engine/World.h"

void UDunceptionGameInstance::Init() 
{
	Super::Init();

	// IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	// 
	// const FString& GameContentDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::GameContentDir());
	// const FString& NewDir = GameContentDir + "WeaponDir";
	// 
	// if (!PlatformFile.DirectoryExists(*NewDir)) {
	// 	if (!PlatformFile.CreateDirectory(*NewDir)) {
	// 		UE_LOG(LogTemp, Error, TEXT("File couldn't be found"));
	// 	}
	// }
	// 
	// const FString& dirforbin = NewDir + "/" + "weaps.mus";
	// 
	// FILE* f1;
	// fopen_s(&f1, TCHAR_TO_ANSI(*dirforbin), "wb");

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	const FString& ContentDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::GameContentDir());
	const FString& NewDir = ContentDir + "Weapons";

	if (!PlatformFile.DirectoryExists(*NewDir)) {
		if (!PlatformFile.CreateDirectory(*NewDir)) {
			FMessageDialog::Debugf(FText::FromString("Directory couldn't created"));
		}
	}

	const FString& DirForBin = NewDir + "/" + "Weapons.wesf";

	// BA = m_weaponAttributes << BA;

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