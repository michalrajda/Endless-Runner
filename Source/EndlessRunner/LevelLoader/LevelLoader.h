// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelLoader.generated.h"

class UBoxComponent;

//Helper class fo loading next sublevel
//In collision channel we ignore everything except Pawn
//On begin overlap we will call function from game instance to load next and unload previous sublevel
UCLASS()
class ENDLESSRUNNER_API ALevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ALevelLoader();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Trigger = nullptr;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector NextSublevelStartPosiiton = { 0.0f,0.0f,0.0f };
};
