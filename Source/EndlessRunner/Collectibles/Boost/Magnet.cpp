// Fill out your copyright notice in the Description page of Project Settings.


#include "Magnet.h"
#include "EndlessRunnerCharacter.h"
#include "Components/SphereComponent.h"


AMagnet::AMagnet()
{
	CollectibleProperty = 500;
}

void AMagnet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(OtherActor))
	{
		UCollectibleProperties* AttachedMagnetProp = Char->GetAttachedProperties(Type);
		if (IsValid(AttachedMagnetProp))
		{
			if (IsValid(AttachedMagnetProp->AttachedCollectible))
			{
				Destroy();
			}
			else if (IsValid(Trigger) && IsValid(Mesh))
			{
				if (Trigger->AttachToComponent(Char->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachedMagnetProp->SocketName))
				{
					Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					SetInstigator(Char);
					SetOwner(Char);
					Trigger->SetSphereRadius(static_cast<float>(CollectibleProperty));
					Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
					AttachedMagnetProp->SetTimer(this);
				}
			}
		}
	}
}
