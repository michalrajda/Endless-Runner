// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

class USpotLightComponent;
class USphereComponent;

UCLASS()
class ENDLESSRUNNER_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:	

	ALamp();

	//Here we calculate new color for light
	virtual void Tick(float DeltaTime) override;

	//In overlaping function we torun on/off ticking and asign overlaping pawn
	//In collision channel we ignore everything except pawn
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Trigger = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpotLightComponent> Light = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	//Max Color will be aplied on max distance (sphere radius)
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor MaxColor = FLinearColor::Green;

	//Min color will be aplied on min distance (at sphere center)
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor MinColor = FLinearColor::Red;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TObjectPtr<AActor> OverlapingCharacter = nullptr;

	//Will be asigned on begin overlap just to not do it every tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	float MaxDistance = 0;
};
