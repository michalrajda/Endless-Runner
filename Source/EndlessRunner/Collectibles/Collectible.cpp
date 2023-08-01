// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "Components/SphereComponent.h"

ACollectible::ACollectible()
{
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
}