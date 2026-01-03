// Fill out your copyright notice in the Description page of Project Settings.


#include "MyviController.h"
// #include "GridCharacter.h"

void AMyviController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("MoveForward", IE_Pressed, this, 
		&AMyviController::InputMoveForward);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, 
		&AMyviController::InputMoveLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, 
		&AMyviController::InputMoveRight);
}

AGridCharacter* AMyviController::GetMyviPawn() const
{
	return Cast<AGridCharacter>(GetMyviPawn());
}

void AMyviController::InputMoveForward()
{
	if (AGridCharacter* Myvi = GetMyviPawn())
	{
		Myvi->MoveForward(); 
	}
}

void AMyviController::InputMoveLeft()
{
	if (AGridCharacter* Myvi = GetMyviPawn())
	{
		Myvi->MoveLeft();
	}
}

void AMyviController::InputMoveRight()
{
	if (AGridCharacter* Myvi = GetMyviPawn())
	{
		Myvi->MoveRight();
	}
}