// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "BoostType.h"
#include "Magnet.generated.h"

//Boost increasing collectible area in Pawn
//When we overlap with Pawn firstly we check if Pawn have still attached Magnet,
//if yes then we destroy
//if not we change collision channel, attach to Pawn and increase sphere radius in Magnet
UCLASS()
class ENDLESSRUNNER_API AMagnet : public ACollectible
{
	GENERATED_BODY()
	
public:	

	AMagnet();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBoostType Type = EBoostType::Magnet;
};
