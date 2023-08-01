// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "BoostType.h"
#include "PointsMultiplier.generated.h"

//Boost increasing multiplier in Pawn
//When we overlap with Pawn firstly we check if Pawn have still attached Points Multiplier,
//if yes then we destroy
//if not we change collision channel, attach to Pawn and increase Multiplier
UCLASS()
class ENDLESSRUNNER_API APointsMultiplier : public ACollectible
{
	GENERATED_BODY()
	
public:	

	APointsMultiplier();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBoostType Type = EBoostType::PointsMultiplier;
};
