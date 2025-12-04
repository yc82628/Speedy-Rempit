#include "VehicleActor.h"

AVehicleActor:AVehicleActor()
{
	PrimaryActorTick.bCanEverTick = true; 

	// Create mesh component
	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	RootComponent = VehicleMesh;

	// Set collision
	VehicleMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	VehicleMesh->SetGenerateOverlapEvents(true);

	// Tagging as a vehicle
	Tags.Add(FName("Vehicle"));
}	

void AVehicleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AVehicleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AVehicleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Vehicle moving in a specific direction
	FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
	SetActorLocation(NewLocation);

	// Destroy if too far from origin (optimisation)
	if (FVector::Dist(NewLocation, FVector::ZeroVector) > 5000.0f)
	{
		Destroy();
	}
}