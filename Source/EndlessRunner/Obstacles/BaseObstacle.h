// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"

class UBoxComponent;

UCLASS()
class ENDLESSRUNNER_API ABaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseObstacle();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Trigger = nullptr;
};
