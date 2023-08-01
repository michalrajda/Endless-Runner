// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameProperties.h"
#include "SaveGameEndlessRunner.generated.h"



UCLASS()
class ENDLESSRUNNER_API USaveGameEndlessRunner : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FSaveGameProperties> Leaderboards;
};
