// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameInstance.h"
#include "EndlessRunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameEndlessRunner.h"
#include "LevelInstance/LevelInstanceLevelStreaming.h"

void UEndlessRunnerGameInstance::Init()
{
	Super::Init();
	LoadSavedGame();
}

void UEndlessRunnerGameInstance::OpenMainMenu(APawn* Pawn, FString& Name)
{
	AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(Pawn);
	if (Char && !Name.IsEmpty())
	{
		LeaderboardList.Emplace(FSaveGameProperties(Name, Char->GetPoints(), Char->GetCoins(), Char->GetDistance()));
		LeaderboardList.Sort();
		if (LeaderboardList.Num() > MaxSizeLeaderboardList)
		{
			LeaderboardList.SetNum(MaxSizeLeaderboardList);
		}
		SaveGame();
	}
	ReturnToMainMenu();
}

void UEndlessRunnerGameInstance::EndGame()
{
	SaveGame();
	ULocalPlayer* LC = (LocalPlayers.Num() > 0) ? LocalPlayers[0] : nullptr;
	if (LC)
	{
		LC->ConsoleCommand("quit");
	}
	else
	{
		GEngine->Exec(GetWorld(), TEXT("quit"));
	}
}

void UEndlessRunnerGameInstance::StartGame()
{
	if (!MainLevel.IsNull())
	{
		if (UWorld* World = GetWorld())
		{
			const FString MainLevelName = FPackageName::ObjectPathToPackageName(MainLevel.ToString());
			FWorldContext& TemporaryWorldContext = GEngine->GetWorldContextFromWorldChecked(World);
			FURL TestURL(&TemporaryWorldContext.LastURL, *MainLevelName, ETravelType::TRAVEL_Absolute);
			if (GEngine->MakeSureMapNameIsValid(TestURL.Map))
			{
				GEngine->SetClientTravel(World, *MainLevelName, ETravelType::TRAVEL_Absolute);
			}
			else
			{
				UE_LOG(LogLevel, Warning, TEXT("WARNING: The map '%s' does not exist."), *TestURL.Map);
			}
		}
	}
	else
	{
		UE_LOG(LogLevel, Warning, TEXT("MainLevelMap is set to null."))
	}
}

bool UEndlessRunnerGameInstance::LoadRandomlyNextSublevel(const FVector& StartLevelPosition)
{
	if (!Sublevels.IsEmpty())
	{
		int32 SublevelIndex = FMath::RandRange(0, Sublevels.Num() - 1);
		return LoadNextSublevelAtIndex(StartLevelPosition, SublevelIndex);
	}
	UE_LOG(LogLevel, Warning, TEXT("Didn't found any sublevels."))
	return false;
}

bool UEndlessRunnerGameInstance::LoadNextSublevelAtIndex(const FVector& StartLevelPosition, const int32 Index)
{
	bool bSucces = false;
	if (Sublevels.IsValidIndex(Index))
	{
		if (IsValid(PreviousLevel))
		{
			PreviousLevel->SetIsRequestingUnloadAndRemoval(true);
		}
		PreviousLevel = ActualLevel;
		ActualLevel = NextLevel;
		const TSoftObjectPtr<UWorld>& LevelToLoad = Sublevels[Index];
		if (!LevelToLoad.IsNull())
		{
			ULevelStreamingDynamic* Level = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, LevelToLoad, FTransform(FRotator::ZeroRotator, StartLevelPosition), bSucces);
			if (bSucces)
			{
				
				NextLevel = Level;
			}
			else
			{
				UE_LOG(LogLevel, Warning, TEXT("Unable to load sublevel at Index: %d."), Index)
			}
		}
		else
		{
			UE_LOG(LogLevel, Warning, TEXT("Sublevel at Index %d is set to null."), Index)
		}
	}
	else
	{
		UE_LOG(LogLevel, Warning, TEXT("Sublevels don't contain Sublevel at Index: %d."), Index)
	}
	return bSucces;
}

void UEndlessRunnerGameInstance::SaveGame()
{
	if (USaveGameEndlessRunner* NewSaveGame = Cast<USaveGameEndlessRunner>(UGameplayStatics::CreateSaveGameObject(USaveGameEndlessRunner::StaticClass())))
	{
		NewSaveGame->Leaderboards = LeaderboardList;
		UGameplayStatics::SaveGameToSlot(NewSaveGame, SaveGameSlotName, SaveGameUserIndex);
	}
}

void UEndlessRunnerGameInstance::LoadSavedGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, SaveGameUserIndex))
	{
		if (USaveGameEndlessRunner* OldSaveGame = Cast<USaveGameEndlessRunner>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, SaveGameUserIndex)))
		{
			LeaderboardList = OldSaveGame->Leaderboards;
		}
	}
}
