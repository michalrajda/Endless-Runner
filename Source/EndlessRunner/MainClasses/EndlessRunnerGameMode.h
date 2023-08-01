// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class AEndlessRunnerCharacter;

//Game Mode for actual game
//When StartPlay is callled we load fist sublevel and wait unitl it will be visible
//then we call StartPlay from AGameModeBase
UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void EndGame(AEndlessRunnerCharacter* Char);

	virtual void StartPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector StartPositionFirstSublevel = { -50.0f, 0.0f, 0.0f };

	UFUNCTION()
	void StartPlayAfterLoadedSublevel();
};



