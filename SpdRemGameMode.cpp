#include "SpdRemGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GridCharacter.h"

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

	if (GEngine)
	{
		GEngine->Ad
	}
}

