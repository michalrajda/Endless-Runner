// Copyright Epic Games, Inc. All Rights Reserved.


#include "BoostSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Collectible.h"

ABoostSpawner::ABoostSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawningArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningArea"));
	SetRootComponent(SpawningArea);
}

void ABoostSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnBoosts();
}

void ABoostSpawner::SpawnBoosts()
{
	if (!BoostClasses.IsEmpty() && IsValid(SpawningArea) && NumberBoostOnLevel)
	{
		if (UWorld* World = GetWorld())
		{
			FBox SpawningBox = SpawningArea->CalcBounds(SpawningArea->GetComponentTransform()).GetBox();
			int32 MaxBoostIndex = BoostClasses.Num() - 1;
			float MinXDistance = (SpawningBox.Max.X - SpawningBox.Min.X) / NumberBoostOnLevel;
			SpawningBox.Max.X = SpawningBox.Min.X + MinXDistance;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.ObjectFlags |= RF_Transient;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
			for (int32 i = 0; i < NumberBoostOnLevel; i++)
			{
				if (UClass* BoostClass = BoostClasses[FMath::RandRange(0, MaxBoostIndex)])
				{
					FVector SpawnLocation = FMath::RandPointInBox(SpawningBox);
					ACollectible* Boost = World->SpawnActor<ACollectible>(BoostClass, SpawnLocation, SpawnRotation, SpawnParam);
				}
				SpawningBox.Min.X += MinXDistance;
				SpawningBox.Max.X += MinXDistance;
			}
		}
	}
}
