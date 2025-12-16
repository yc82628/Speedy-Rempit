#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "GridCharacter.generated.h"

UCLASS()
class SPDREM_API AGridCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGridCharacter();

protected: 
	virtual void BeginPlay() override;

public: 
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Grid Movement")
	float GridSize = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Movement")
	float MovementSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Movement")
	bool bIsMoving = false;

	//Collision
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* CollisionBox;

	// Audio (BP assign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* naSound;  // driving forward sound

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* CrashSound; // crash

private:
	// Movement functions
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	// Grid tracking positions
	FVector CurrentGridPosition;
	FVector TargetGridPosition;
	float MovementProgress = 0.0f;
	int32 ForwardProgress = 0;

	// Helper functions
	FVector WorldToGrid(FVector& WorldPosition) const;
	FVector GridToWorld(FVector& GridPosition) const;

	// Collision
	UFUNCTION()
	void OnCollisionOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult& SweepResult
	);

	// Audio 
	void Play_naSound();
	void PlayCrashSound();
};