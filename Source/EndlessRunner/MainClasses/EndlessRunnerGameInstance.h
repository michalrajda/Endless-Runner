// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameProperties.h"
#include "EndlessRunnerGameInstance.generated.h"

class APawn;
class APlayerController;
class ULevelStreamingDynamic;

//In GameInstance we handle loading and unloading levels and sublevels
//On Init we load SaveGame (there is stored array witch leaderboards)
UCLASS()
class ENDLESSRUNNER_API UEndlessRunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	void OpenMainMenu(APawn* Pawn, FString& Name);

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void StartGame();

	bool LoadRandomlyNextSublevel(const FVector& StartLevelPosition);

	bool LoadNextSublevelAtIndex(const FVector& StartLevelPosition, const int32 Index);

	FORCEINLINE const TArray<FSaveGameProperties>& GetLeaderboardList() const { return LeaderboardList; }

	FORCEINLINE int32 GetMaxSizeLeaderboardList() const { return MaxSizeLeaderboardList; }

	FORCEINLINE ULevelStreamingDynamic* GetNextLevel() const { return NextLevel; }

protected:

	void SaveGame();

	void LoadSavedGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, noClear)
	TSoftObjectPtr<UWorld> MainLevel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, noClear)
	TArray<TSoftObjectPtr<UWorld>> Sublevels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TArray<FSaveGameProperties> LeaderboardList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	ULevelStreamingDynamic* PreviousLevel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	ULevelStreamingDynamic* ActualLevel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	ULevelStreamingDynamic* NextLevel = nullptr;

	UPROPERTY(EditAnywhere)
	int32 MaxSizeLeaderboardList = 10;

	UPROPERTY(EditAnywhere)
	FString SaveGameSlotName = TEXT("SaveSlot0");

	UPROPERTY(EditAnywhere)
	uint32 SaveGameUserIndex = 0;
};
