// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraMover.generated.h"

class USplineComponent;
class UBoxComponent;
class USpringArmComponent;

UCLASS()
class DUNCEPTION_API ACameraMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraMover();

	UPROPERTY(EditInstanceOnly)
		UBoxComponent* StartTrigger;

	UPROPERTY(EditInstanceOnly)
		UBoxComponent* EndTrigger;

	UPROPERTY(EditInstanceOnly)
		USplineComponent* CameraSplinePath;

	UPROPERTY(EditInstanceOnly)
		USceneComponent* StartTriggerTransform;

	UPROPERTY(EditInstanceOnly)
		USceneComponent* EndTriggerTransform;

	UPROPERTY(EditInstanceOnly)
		USceneComponent* CamRoot;

	UFUNCTION()
		void OnCameraBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	USpringArmComponent* PlayerCamera;
	float timer = 0.0f;
};
