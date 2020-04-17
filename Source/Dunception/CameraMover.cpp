// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMover.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DefaultCharacter.h"
#include "DrawDebugHelpers.h"
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
	StartTrigger->OnComponentEndOverlap.AddDynamic(this, &ACameraMover::OnCameraBeginEnd);

	EndTriggerTransform = CreateDefaultSubobject<USceneComponent>(TEXT("End Trigger Transform"));
	EndTriggerTransform->AttachTo(CamRoot);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("End Trigger"));
	EndTrigger->SetupAttachment(EndTriggerTransform);
	EndTrigger->bHiddenInGame = false;
	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraMover::OnCameraEnd);
	EndTrigger->OnComponentEndOverlap.AddDynamic(this, &ACameraMover::OnCameraEndEnd);

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
			// CameraSplinePath->SetLocationAtSplinePoint(CameraSplinePath->GetNumberOfSplinePoints() - 1, EndTriggerTransform->GetComponentLocation(), ESplineCoordinateSpace::World);
		if (OurGuy) {

			FHitResult OutHit;
			FVector TraceStart = StartTriggerTransform->GetComponentLocation();
			FVector TraceEnd = EndTriggerTransform->GetComponentLocation();

			GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldDynamic);
			if (OutHit.Actor == OurGuy) {
				bIsHeHitLineTrace = true;
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0.0f, 3.0f);
			}

			else {
				bIsHeHitLineTrace = false;
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0.0f, 3.0f);
			}

			FVector LastSplineKeyLoc = CameraSplinePath->GetLocationAtSplineInputKey(CameraSplinePath->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
			UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(StartTriggerTransform->GetComponentLocation(), OurGuy->GetActorLocation()));
			// UE_LOG(LogTemp, Warning, TEXT("%s"), *CameraSplinePath->GetLocationAtDistanceAlongSpline(timer, ESplineCoordinateSpace::World).ToString());
			// timer += DeltaTime * 600;
			FVector LastSplineNewLoc = FVector(LastSplineKeyLoc.X, LastSplineKeyLoc.Y, OurGuy->CameraLocation->GetComponentLocation().Z);
			CameraSplinePath->SetLocationAtSplinePoint(CameraSplinePath->GetNumberOfSplinePoints() - 1, LastSplineNewLoc, ESplineCoordinateSpace::World);

			PlayerDistance = FVector::Distance(FVector(0.0f, StartTriggerTransform->GetComponentLocation().Y, 0.0f), FVector(0.0f, OurGuy->GetActorLocation().Y, 0.0f));
			// UE_LOG(LogTemp, Warning, TEXT("%f"), timer);
			PlayerCamera->SetWorldLocation(CameraSplinePath->GetLocationAtDistanceAlongSpline(PlayerDistance, ESplineCoordinateSpace::World));
		}
	}
}

void ACameraMover::OnCameraBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsOurGuyInside) {
		bIsOurGuyInside = true;
		if (OtherActor->IsA<ADefaultCharacter>()) {
			OurGuy = Cast<ADefaultCharacter>(OtherActor);
			PlayerCamera = OurGuy->SpringArm;
			CameraSplinePath->SetLocationAtSplinePoint(0, OurGuy->CameraLocation->GetComponentLocation(), ESplineCoordinateSpace::World);
		}
	}

	if (bIsOurGuyInside) {
		// Nothing
	}
}

void ACameraMover::OnCameraEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsOurGuyInside) {
		bIsOurGuyInside = true;
		if (OtherActor->IsA<ADefaultCharacter>()) {
			OurGuy = Cast<ADefaultCharacter>(OtherActor);
			PlayerCamera = OurGuy->SpringArm;
			// CameraSplinePath->SetLocationAtSplinePoint(0, OurGuy->CameraLocation->GetComponentLocation(), ESplineCoordinateSpace::World);
		}
	}
	else {
		OurGuy = nullptr;
	}
}

void ACameraMover::OnCameraBeginEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (bIsHeHitLineTrace) {
		// Do Nothing
	}
	else {
		if (OurGuy) {
			OurGuy->SpringArm->SetRelativeLocation(OurGuy->CameraLocation->GetComponentLocation());
			OurGuy = nullptr;
		}
	}
}

void ACameraMover::OnCameraEndEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsHeHitLineTrace) {
		// Do Nothing
	}
	else {
		if (OurGuy) {
			OurGuy->SpringArm->SetRelativeLocation(OurGuy->CameraLocation->GetComponentLocation());
			OurGuy = nullptr;
		}
	}
}

