// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTextureGenerator.generated.h"

class USceneCaptureComponent2D;

UCLASS()
class DUNCEPTION_API AWeaponTextureGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponTextureGenerator();

	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
	USceneComponent* WeaponScene;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
