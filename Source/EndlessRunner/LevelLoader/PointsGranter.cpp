// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsGranter.h"
#include "EndlessRunnerCharacter.h"
#include "Components/BoxComponent.h"

APointsGranter::APointsGranter()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
}

void APointsGranter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(OtherActor))
	{
		Char->IncreaseMaxSpeed(Points, DeltaSpeed);
	}
}

