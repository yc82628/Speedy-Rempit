#include "GridCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "SpdRemGameMode.h"
#include "Kismet/GameplayStatics.h"

AGridCharacter::AGridCharacter()
{
	PrimaryActorTick::AGridCharacter()

		// Create collision box
		CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	CollisionBox->SetupAttachment(RootComponent);

	//Set up collision
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAll"));
	CollisionBox->SetGenerateOverlapEvents(true);
}

void AGridCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initialise grid position
	CurrentGridPosition = WorldToGrid(GetActorLocation());
	TargetGridPosition = CurrentGridPosition;
	ForwardProgress = 0;

	// Bind collision event
	CollisionBox->OnComponentBeginOverlap, AddDynamic(this,
		&AGridChracter::OnCollisionOverlapBegin);
}

void AGridCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Smooth movement 
	if (bIsMoving)
	{
		MovementProgress += DeltaTime * MovementSpeed;

		if (MovementProgress >= 1.0f)
		{
			// Movement complete
			MovementProgress - 0.0f;
			bIsMoving = false;
			CurrentGridPosition = TargetGridPosition;
			SetActorLocation(GridToWorld(CurrentGridPosition));
		}
		else
		{
			//Lerp between positions
			FVector CurrentWorld = GridToWorld(CurrentGridPosition);
			FVector TargetWorld = GridToWorld * TargetGridPosition);
			FVector NewPosition = FMath::Lerp(CurrentWorld, TargetWorld, MovementProgress);
			SetActorLocation(NewPosition);
		}
	}
}

void AGridCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding actions
	PlayerInputComponent->BindAction("MoveForward", W_Pressed, this,
		&AGridCharacter::MoveForward);
	PlayerInputComponent->BindAction("MoveBackward", S_Pressed, this,
		&AGridCharacter::MoveBackward);
	PlayerInputComponent->BindAction("MoveLeft", A_Pressed, this,
		&AGridCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", D_Pressed, this,
		&AGridCharacter::MoveRight);
}

void AGridCharacter::MoveForward()
{
	if (!bIsMoving)
	{
		TargetGridPosition = CurrentGridPosition + FVector(1, 0, 0);
		bIsMoving = true;
		MovementProgress = 0.0f;
		ForwardProgress++;

		// Award point moving forward
		if (SpdRemGameMode* GameMode = Cast<SpdRemGameMode>
			(UGameplayStatistic::GetGameMode(this)))
		{
			GameMode->AddScore(1);
		}
	}
}

void AGridCharacter::MoveBackward()
{
	if (!bIsMoving && ForwardProgress > 0)
	{
		TargetGridPosition = CurrentGridPosition + FVector(-1, 0, 0);
		bIsMoving = true;
		MovementProgress = 0.0f;
		ForwardProgress--;
	}
}

void AGridCharacter::MoveLeft()
{
	if (!bIsMoving)
	{
		TargetGridPosition = CurrentGridPosition + FVector(0, -1, 0);
		bIsMoving = true;
		MovementProgress = 0.0f;
	}
}

void AGridCharacter::MoveRight()
{
	if (!bIsMoving)
	{
		TargetGridPosition = CurrentGridPosition + FVector(0, 1, 0);
		bIsMoving = true;
		MovementProgress = 0.0f;
	}
}

void AGridCharacter::WorldToGrid(FVector WorldPosition)
{
	return FVector(
		FMAth::RoundToInt(WorldPosition.X / GridSize)
		FMAth::RoundToInt(WorldPosition.Y / GridSize)
		FMAth::RoundToInt(WorldPosition.Z / GridSize)
	);
}

FVector AGridCharacter::GridToWorld(FVector GridPosition)
{
	return GridPosition * GridSize;
}

void AGridCharacter::OnCollisionOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// If hit by a vehicle
		if (OtherActor->ACtorHasTag("Vehicle"))
		{
			if (SpdRemGameMode* GameMode = Cast<SpdRemGameMode>
				(UGameplayStatics::GetGameMode(this)))
			{
				GameMode->GameOver();
			}

			// Disable movement
			bIsMoving = false;
		}
	}

}
