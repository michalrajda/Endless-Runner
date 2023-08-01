// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointsContainerWidget.generated.h"

class UTextBlock;

UCLASS()
class ENDLESSRUNNER_API UPointsContainerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized();

	void OnPlayerPickUpCoin(int32 InCoinsNumber, int32 InPoints);

	void OnPlayerChangeDistance(int32 InDistance);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CoinsText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> DistanceText = nullptr;
};
