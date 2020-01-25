// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/FileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"

/**
 * 
 */
class DUNCEPTION_API DunceptionFileHandler
{
public:
	DunceptionFileHandler();
	~DunceptionFileHandler();
	
	/*Returns 0 if its succesfull*/
	template<typename T>
	static bool WriteToFile(const FString& Directory, const FString& FileName, const FString& FileExtension, T& StructureToWriteData);

};
