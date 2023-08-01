// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoader.h"
#include "Components/BoxComponent.h"
#include "EndlessRunnerCharacter.h"
#include "EndlessRunnerGameInstance.h"

ALevelLoader::ALevelLoader()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
}

void ALevelLoader::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
	{
		if (IsValid(Trigger))
		{
			GI->LoadRandomlyNextSublevel(Trigger->GetComponentTransform().GetTranslation() + NextSublevelStartPosiiton);
		}
	}
}
