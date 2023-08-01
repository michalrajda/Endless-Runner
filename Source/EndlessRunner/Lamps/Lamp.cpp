// Fill out your copyright notice in the Description page of Project Settings.

#include "Lamp.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"

ALamp::ALamp()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bAllowTickBeforeBeginPlay = false;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
}

void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(OverlapingCharacter) && IsValid(Light))
	{
		const float Distance = FVector::Dist2D(OverlapingCharacter->GetActorLocation(), GetActorLocation());
		const float Alfa = FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
		const FLinearColor NewColor = MinColor + Alfa * (MaxColor - MinColor);
		Light->SetLightColor(NewColor);
	}
}

void ALamp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ReceiveActorBeginOverlap(OtherActor);
	if (IsValid(OtherActor))
	{
		OverlapingCharacter = OtherActor;
		MaxDistance = IsValid(Trigger) ? Trigger->GetScaledSphereRadius() : 1.0f;
		SetActorTickEnabled(true);
	}
}

void ALamp::NotifyActorEndOverlap(AActor* OtherActor)
{
	ReceiveActorEndOverlap(OtherActor);
	if (OtherActor == OverlapingCharacter)
	{
		SetActorTickEnabled(false);
		OverlapingCharacter = nullptr;
	}
}

void ALamp::OnConstruction(const FTransform& Transform)
{
	if (IsValid(Light))
	{
		Light->SetLightColor(MaxColor);
	}
}

