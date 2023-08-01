// Copyright Epic Games, Inc. All Rights Reserved.


#include "CoinSpawner.h"
#include "Coin.h"

ACoinSpawner::ACoinSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnCoins();
}

void ACoinSpawner::SpawnCoins()
{
	if (IsValid(CoinClass) && IsValid(RootComponent))
	{
		if (UWorld* World = GetWorld())
		{
			FVector SpawnerLocation = RootComponent->GetComponentTransform().GetTranslation();
			for (const FCoinSpawningProperties& SpawnProp : CoinSpawningProps)
			{
				int32 NumRow = FMath::RandRange(0, RowInLevel - 1);
				FVector SpawnLocation = SpawnerLocation + SpawnProp.SpawningStartPosition;
				FRotator SpawnRotation = FRotator::ZeroRotator;
				FActorSpawnParameters SpawnParam;
				SpawnParam.Owner = this;
				SpawnParam.ObjectFlags |= RF_Transient;
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
				SpawnLocation.Y += NumRow * RowSizeInLevel;
				int32 MaxCoin = SpawnProp.NumberOfCoin;
				for (int32 i = 0; i < MaxCoin; i++)
				{
					ACoin* Coin = World->SpawnActor<ACoin>(CoinClass, SpawnLocation, SpawnRotation, SpawnParam);
					SpawnLocation.X += DistanceToNextCoin;
				}
			}
		}
	}
}