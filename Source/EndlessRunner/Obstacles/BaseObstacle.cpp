// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObstacle.h"
#include "Components/BoxComponent.h"
#include "EndlessRunnerCharacter.h"
#include "EndlessRunnerGameMode.h"

ABaseObstacle::ABaseObstacle()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
}

void ABaseObstacle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(OtherActor))
	{
		if (UWorld* Wordl = GetWorld())
		{
			if (AEndlessRunnerGameMode* GM = Wordl->GetAuthGameMode<AEndlessRunnerGameMode>()) 
			{
				GM->EndGame(Char);
			}
		}
	}
}
