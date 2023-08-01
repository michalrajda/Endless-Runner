// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardsSlotWidget.h"
#include "SaveGameProperties.h"
#include "Components/TextBlock.h"

void ULeaderboardsSlotWidget::SetPropertiesInSlot(const FSaveGameProperties& InSaveGameProperties, int32 InPosition)
{
	if (IsValid(Position) && IsValid(NameText) && IsValid(PointsText) && IsValid(CoinsText) && IsValid(DistanceText))
	{
		Position->SetText(FText::AsNumber(InPosition));
		NameText->SetText(FText::FromString(InSaveGameProperties.Name));
		PointsText->SetText(FText::AsNumber(InSaveGameProperties.Points));
		CoinsText->SetText(FText::AsNumber(InSaveGameProperties.Coins));
		DistanceText->SetText(FText::AsNumber(InSaveGameProperties.Distance));
	}
}