// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class USphereComponent;

UCLASS()
class ENDLESSRUNNER_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACollectible();

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	FORCEINLINE USphereComponent* GetTrigger() const { return Trigger; }

	//Get default Property for all Collectible (for Coin this will be Points, for Magnet new Radius, for PointsMultiplier Multiplier)
	FORCEINLINE int32 GetCollectibleProperty() const { return CollectibleProperty; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Trigger = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Default Property for all Collectible (for Coin this will be Points, for Magnet new Radius)"))
	int32 CollectibleProperty = 1;
};
