// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointsGranter.generated.h"

class UBoxComponent;

//Class for granding points and increasing Pawn's speed
//Is should be plased at the oend of sublevel
UCLASS()
class ENDLESSRUNNER_API APointsGranter : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APointsGranter();

	//In collision channel we only overlap with pawn, the rest are ignored
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Trigger = nullptr;

	UPROPERTY(EditAnywhere)
	int32 Points = 100;

	UPROPERTY(EditAnywhere)
	float DeltaSpeed = 50.0f;
};
