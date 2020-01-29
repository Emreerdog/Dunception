// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponMerchant.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class ADefaultCharacter;
class AMainMapState;

UCLASS(BlueprintType)
class DUNCEPTION_API AWeaponMerchant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponMerchant();

	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* MerchantMesh;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* MerchantInteractionArea;

	UFUNCTION()
		void EnableMerchantPanel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void DisableMerchantPanel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void AssignWeaponRowsAndColoumns();

	UPROPERTY(BlueprintReadOnly)
		bool bIsCharacterOverlapping = false;

	UPROPERTY(BlueprintReadOnly)
		bool bIsCharacterInteracting = false;

	UPROPERTY(BlueprintReadOnly)
		int Coloumn;

	UPROPERTY(BlueprintReadOnly)
		int Row;

	UPROPERTY(BlueprintReadOnly)
		bool bIsAssignmentFinished = false;

	UPROPERTY(BlueprintReadOnly)
		int WeaponID;

	UPROPERTY(BlueprintReadOnly)
		float WeaponDamage;

	UPROPERTY(BlueprintReadOnly)
		FString WeaponName;

	UPROPERTY(BlueprintReadOnly)
		FString WeaponDescription;

	UPROPERTY(BlueprintReadOnly)
		float WeaponCost;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	ADefaultCharacter* OverlappedGuy;
	AMainMapState* MainMapState;

};
