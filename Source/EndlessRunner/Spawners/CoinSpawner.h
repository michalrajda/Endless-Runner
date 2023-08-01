// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

class ACoin;

//Helper struct with spawning properites
USTRUCT(BlueprintAble)
struct ENDLESSRUNNER_API FCoinSpawningProperties
{
	GENERATED_BODY()

public:

	//X and Z coordinates are taken from here, Y coordinates are chosen randomly depending from size of coin and size of sublevel
	//It should be placed in most left side of sublevel
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector SpawningStartPosition = FVector::ZeroVector;

	//How much coin should be spawned in X direction
	UPROPERTY(EditAnywhere)
	int32 NumberOfCoin = 0;
};

UCLASS()
class ENDLESSRUNNER_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ACoinSpawner();

protected:

	virtual void BeginPlay() override;

	void SpawnCoins();

	UPROPERTY(EditDefaultsOnly, noClear, meta = (BlueprintBaseOnly))
	TSubclassOf<ACoin> CoinClass = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<FCoinSpawningProperties> CoinSpawningProps;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Coin size and distnace between coins"))
	float DistanceToNextCoin = 74.0f;

	UPROPERTY(EditAnywhere)
	int32 RowInLevel = 3;

	UPROPERTY(EditAnywhere)
	float RowSizeInLevel = 100.0f;
};
