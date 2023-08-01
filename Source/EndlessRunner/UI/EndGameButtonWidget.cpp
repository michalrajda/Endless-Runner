// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameButtonWidget.h"
#include "Components/Button.h"
#include "EndlessRunnerGameInstance.h"

void UEndGameButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IsValid(Button))
	{
		if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
		{
			Button->OnClicked.AddDynamic(GI, &UEndlessRunnerGameInstance::EndGame);
		}
	}
}
