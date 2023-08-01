// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageWidget.h"
#include "Components/TextBlock.h"
#include "EndlessRunnerHUD.h"

void UMessageWidget::SetMessages(const int32 FirstParamToShow, const int32 SecondParamToShow)
{
	if (IsValid(MessageText1) && IsValid(MessageText2))
	{
		MessageText1->SetText(FText::AsNumber(FirstParamToShow));
		MessageText2->SetText(FText::AsNumber(SecondParamToShow));
	}
}

void UMessageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AEndlessRunnerHUD* HUD = PC->GetHUD<AEndlessRunnerHUD>())
		{
			HUD->AddMessageWidget(this);
		}
	}
}
