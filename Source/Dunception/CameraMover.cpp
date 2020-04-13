// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMover.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DefaultCharacter.h"
#include "Components/SplineComponent.h"

// Sets default values
ACameraMover::ACameraMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CamRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	CamRoot->SetupAttachment(RootComponent);

	StartTriggerTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Start Trigger Transform"));
	StartTriggerTransform->AttachTo(CamRoot);

	StartTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Start Trigger"));
	StartTrigger->SetupAttachment(StartTriggerTransform);
	StartTrigger->bHiddenInGame = false;
	StartTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraMover::OnCameraBegin);

	EndTriggerTransform = CreateDefaultSubobject<USceneComponent>(TEXT("End Trigger Transform"));
	EndTriggerTransform->AttachTo(CamRoot);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("End Trigger"));
	EndTrigger->SetupAttachment(EndTriggerTransform);
	EndTrigger->bHiddenInGame = false;

	CameraSplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Camera Spline Path"));
	CameraSplinePath->SetVisibility(true);
	CameraSplinePath->AttachTo(StartTriggerTransform);


}

// Called when the game starts or when spawned
void ACameraMover::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ACameraMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraSplinePath) {
		CameraSplinePath->SetLocationAtSplinePoint(CameraSplinePath->GetNumberOfSplinePoints() - 1, EndTriggerTransform->GetComponentLocation(), ESplineCoordinateSpace::World);
		if (PlayerCamera) {
			UE_LOG(LogTemp, Warning, TEXT("%s"), *CameraSplinePath->GetLocationAtDistanceAlongSpline(timer, ESplineCoordinateSpace::World).ToString());
			timer += DeltaTime * 600;
			PlayerCamera->SetWorldLocation(CameraSplinePath->GetLocationAtDistanceAlongSpline(timer, ESplineCoordinateSpace::World));
		}
	}
}

void ACameraMover::OnCameraBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ADefaultCharacter>()) {
		ADefaultCharacter* tempDef = Cast<ADefaultCharacter>(OtherActor);
		PlayerCamera = tempDef->SpringArm;
	}
}

