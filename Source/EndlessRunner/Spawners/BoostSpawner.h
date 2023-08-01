// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostSpawner.generated.h"

class ACollectible;
class UBoxComponent;

UCLASS()
class ENDLESSRUNNER_API ABoostSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABoostSpawner();

protected:
	
	virtual void BeginPlay() override;

	//Boost's class and position will be chosen randomly
	void SpawnBoosts();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> SpawningArea = nullptr;

	UPROPERTY(EditAnywhere, noClear, meta = (BlueprintBaseOnly))
	TArray<TSubclassOf<ACollectible>> BoostClasses;

	UPROPERTY(EditAnywhere)
	int32 NumberBoostOnLevel = 2;
};
