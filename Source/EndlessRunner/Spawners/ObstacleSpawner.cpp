// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "BaseObstacle.h"


AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnObstacles();
}

void AObstacleSpawner::SpawnObstacles()
{
	if (!ObstacleSpawningProperties.IsEmpty() && IsValid(RootComponent) && !SpawningLocations.IsEmpty())
	{
		if (UWorld* World = GetWorld())
		{
			const FVector SpawnerLocation = RootComponent->GetComponentTransform().GetTranslation();
			const float MaxSize = RowInLevel * RowSizeInLevel;
			int32 MaxObstacleIndex = ObstacleSpawningProperties.Num() - 1;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.ObjectFlags |= RF_Transient;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
			for (const FVector& Position : SpawningLocations)
			{
				const UObstacleSpawningProperties* SpawnProp = ObstacleSpawningProperties[FMath::RandRange(0, MaxObstacleIndex)];
				if (IsValid(SpawnProp))
				{
					if (UClass* ObstacleClass = SpawnProp->ClassToSpawn)
					{
						FVector SpawnLocation = SpawnerLocation + Position;
						SpawnLocation.Z += SpawnProp->ObstacleHalfSizeZ;
						SpawnLocation.Z += FMath::RandRange(0, 1) * VerticalDistance;
						float MinSpawnY = SpawnProp->ObstacleHalfSizeY;
						float MaxSpawnY = MaxSize - SpawnProp->ObstacleHalfSizeY;
						SpawnLocation.Y += static_cast<int32>(FMath::RandRange(MinSpawnY, MaxSpawnY) / SpawnProp->ObstacleHalfSizeY) * SpawnProp->ObstacleHalfSizeY;
						World->SpawnActor<ABaseObstacle>(ObstacleClass, SpawnLocation, SpawnRotation, SpawnParam);
					}
				}
			}
		}
	}
}
