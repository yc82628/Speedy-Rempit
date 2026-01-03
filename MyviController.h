// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyviController.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDY_REMPIT_V2_API AMyviController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

	// Input handlers
	void InputMoveForward();
	void InputMoveRight();
	void InputMoveLeft();

	//Helper on Car pawn
	class AGridCharacter* GetMyviPawn() const;
};

