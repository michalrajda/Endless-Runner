// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "EndlessRunnerHUD.h"
#include "EndlessRunnerGameInstance.h"
#include "LevelInstance/LevelInstanceLevelStreaming.h"

void AEndlessRunnerGameMode::EndGame(AEndlessRunnerCharacter* Char)
{
	if (IsValid(Char))
	{
		if (APlayerController* PC = Char->GetPlayerController<APlayerController>())
		{
			SetPause(PC);
			if (AEndlessRunnerHUD* HUD = PC->GetHUD<AEndlessRunnerHUD>())
			{
				HUD->ShowEnterNameWidget();
			}
		}
	}
}

void AEndlessRunnerGameMode::StartPlay()
{
	if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
	{
		if (GI->LoadNextSublevelAtIndex(StartPositionFirstSublevel, 0))
		{
			ULevelStreamingDynamic* NextLevel = GI->GetNextLevel();
			if (NextLevel->IsLevelVisible())
			{
				Super::StartPlay();
			}
			else
			{
				NextLevel->OnLevelShown.AddDynamic(this, &AEndlessRunnerGameMode::StartPlayAfterLoadedSublevel);
			}
		}
		else
		{
			UE_LOG(LogLevel, Warning, TEXT("Unable to load sublevel, return to main menu"))
			GI->ReturnToMainMenu();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not derived from : %s"), *UEndlessRunnerGameInstance::StaticClass()->GetName())
		GetGameInstance()->ReturnToMainMenu();
	}
}

void AEndlessRunnerGameMode::StartPlayAfterLoadedSublevel()
{
	if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
	{
		if (ULevelStreamingDynamic* NextLevel = GI->GetNextLevel())
		{
			NextLevel->OnLevelShown.RemoveDynamic(this, &AEndlessRunnerGameMode::StartPlayAfterLoadedSublevel);
		}
	}
	Super::StartPlay();
}
