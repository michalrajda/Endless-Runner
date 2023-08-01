// Fill out your copyright notice in the Description page of Project Settings.

#include "PointsMultiplier.h"
#include "EndlessRunnerCharacter.h"
#include "Components/SphereComponent.h"

APointsMultiplier::APointsMultiplier()
{
	PrimaryActorTick.bCanEverTick = false;
	CollectibleProperty = 5;
}

void APointsMultiplier::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if(AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(OtherActor))
	{
		UCollectibleProperties* AttachedMultiplierProp = Char->GetAttachedProperties(Type);
		if (IsValid(AttachedMultiplierProp))
		{
			if (IsValid(AttachedMultiplierProp->AttachedCollectible))
			{
				Destroy();
			}
			else if (IsValid(Trigger) && IsValid(Mesh))
			{
				if (Trigger->AttachToComponent(Char->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachedMultiplierProp->SocketName))
				{
					Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					Char->SetMultiplier(CollectibleProperty);
					AttachedMultiplierProp->SetTimer(this);
				}
			}
		}
	}
}

