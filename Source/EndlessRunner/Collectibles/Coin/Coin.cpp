// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/SphereComponent.h"
#include "EndlessRunnerCharacter.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	CollectibleProperty = 1;
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(Trigger))
	{
		const FQuat NewWorldRotation = CoinRotation * Trigger->GetComponentTransform().GetRotation();
		Trigger->SetWorldRotation(NewWorldRotation);
	}
}

void ACoin::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (IsValid(OtherActor))
	{
		if (AEndlessRunnerCharacter* Char = OtherActor->GetInstigator<AEndlessRunnerCharacter>())
		{
			Char->AddCoin(CollectibleProperty);
			Destroy();
		}
	}
}
