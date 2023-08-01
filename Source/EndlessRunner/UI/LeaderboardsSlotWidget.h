// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardsSlotWidget.generated.h"

class UTextBlock;
struct FSaveGameProperties;

UCLASS()
class ENDLESSRUNNER_API ULeaderboardsSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPropertiesInSlot(const FSaveGameProperties& InSaveGameProperties, int32 InPosition);
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Position = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CoinsText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> DistanceText = nullptr;
};
