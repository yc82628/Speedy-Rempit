#include "SpdRemGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GridCharacter.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"

SpdRemGameMode::SpdRemGameMode()
{
	CurrentScore = 0;
	HighSCore = 0;
	bIsGameOver = false;

	//Set default class to my grid character
	DefaultClass = AGridCharacter::StatiClass();
}

void SpdRemGameMode::StartPlay()
{
	Super::StartPlay();

	CurrentScore = 0;
	bIsGameOver = false;

	if (BackgroundMusic)
	{
		// 0.0f volume multiplier, 1.0f pitch, 0.0f start time, looping by default in cue/asset
		UGameplayStatics::PlaySound2D(this, BackgroundMusic);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Speedy Rempit Game Start!")
	}
}

void SpdRemGameMode::AddScore(int32 Points)
{
	if (!bIsGameOver)
	{
		return;
	}

	CurrentScore += Points;
	if (CurrentScore > HighScore)
	{
		HighScore = CurrentScore;
	}
}

void SpdRemGameMode::GameOver()
{
	bIsGameOver = true;

	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("Game Over! Final Score: %d"), Current Score);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);
	}
}

void SpdRemGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}


