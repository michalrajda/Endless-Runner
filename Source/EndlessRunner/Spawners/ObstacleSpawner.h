// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "ObstacleSpawner.generated.h"

class ABaseObstacle;

//Helper class for storing obstalce's properites
//We assume that pawn will move in x direction
UCLASS()
class ENDLESSRUNNER_API UObstacleSpawningProperties : public UDataAsset
{
	GENERATED_BODY()

public:

	//Coordinates are in word direstion
	//z is Up and y is Right
	UPROPERTY(EditAnywhere)
	float ObstacleHalfSizeY = 50.0f;

	UPROPERTY(EditAnywhere)
	float ObstacleHalfSizeZ = 50.0f;

	//Class to spawn
	UPROPERTY(EditAnywhere, noClear, meta = (BlueprintBaseOnly))
	TSubclassOf<ABaseObstacle> ClassToSpawn = nullptr;
};

//Class handling spawnig obstacles
//It should be placed in world with minimum 1.0f offset in up direction and in most left side 
UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AObstacleSpawner();

protected:

	virtual void BeginPlay() override;

	void SpawnObstacles();

	//Class to spawn will be randomly chosen from array
	UPROPERTY(EditAnywhere, noClear)
	TArray<TObjectPtr<UObstacleSpawningProperties>> ObstacleSpawningProperties;

	//Array with start spawning location, here basicly we just specify x coordinates
	//y coordinates will be chosen randomly depengind from size of sublevel and size of obstacle
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	TArray<FVector> SpawningLocations;

	UPROPERTY(EditAnywhere)
	int32 RowInLevel = 3;

	UPROPERTY(EditAnywhere)
	float RowSizeInLevel = 100.0f;

	//We will also draw a Z coordinates, this offset will be applied if obstacles should "fly"
	UPROPERTY(EditAnywhere)
	float VerticalDistance = 55.0;
};
