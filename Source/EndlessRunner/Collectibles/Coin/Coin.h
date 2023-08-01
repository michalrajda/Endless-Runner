// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "Coin.generated.h"

class USphereComponent;

UCLASS()
class ENDLESSRUNNER_API ACoin : public ACollectible
{
	GENERATED_BODY()
	
public:	

	ACoin();

	//In tick function we rotate coin
	virtual void Tick(float DeltaTime) override;

	//In collision channel we overlap only with Pawn, the rest is blocked
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	FQuat CoinRotation = { 0.0f,0.0f,1.0f,0.0f };
};
