#pragma once

#include ".h"
#include "GameFramework/GameModeBase.h"
#include "SpdRemGameMode.generated.h"

UCLASS()
class SPDREMPIT_API SpdRepGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	SpdRepGameMode();

protected:
	virtual void StartPlay() override;

public:
	// Score Tracking 
	UPROPERTY(BlueprintintReadOnly, Category = "Game State")
	int32 CurrentScore;

	UPROPERTY(BlueprintintReadOnly, Category = "Game State")
	int32 HighScore;

	UPROPERTY(BlueprintintReadOnly, Category = "Game State")
	bool bIsGameOver;

	// Game state functions
	UFUNCTION(BlueprintintCallable, Category = "Game State")
	void AddScore(int32 Points);

	UFUNCTION(BlueprintintCallable, Category = "Game State")
	void GameOver();

	UFUNCTION(BlueprintintCallable, Category = "Game State")
	void RestartGame();
};