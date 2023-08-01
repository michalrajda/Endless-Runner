// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameButtonWidget.h"
#include "Components/Button.h"
#include "EndlessRunnerGameInstance.h"

void UStartGameButtonWidget::NativeOnInitialized()
{
	if (IsValid(Button))
	{
		if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
		{
			Button->OnClicked.AddDynamic(GI, &UEndlessRunnerGameInstance::StartGame);
		}
	}
}
