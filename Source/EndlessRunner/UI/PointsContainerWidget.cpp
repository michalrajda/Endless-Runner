// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsContainerWidget.h"
#include "EndlessRunnerCharacter.h"
#include "Components/TextBlock.h"

void UPointsContainerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (AEndlessRunnerCharacter* Char = GetOwningPlayerPawn<AEndlessRunnerCharacter>())
	{
		Char->OnPlayerPickUpCoin.BindUObject(this, &UPointsContainerWidget::OnPlayerPickUpCoin);
		Char->OnPlayerChangeDistance.BindUObject(this, &UPointsContainerWidget::OnPlayerChangeDistance);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Character not available"))
	}
}

void UPointsContainerWidget::OnPlayerPickUpCoin(int32 InCoinsNumber, int32 InPoints)
{
	if (IsValid(CoinsText))
	{
		CoinsText->SetText(FText::AsNumber(InCoinsNumber));
	}
	if (IsValid(PointsText))
	{
		PointsText->SetText(FText::AsNumber(InPoints));
	}
}

void UPointsContainerWidget::OnPlayerChangeDistance(int32 InDistance)
{
	if (IsValid(DistanceText))
	{
		DistanceText->SetText(FText::AsNumber(InDistance));
	}
}
