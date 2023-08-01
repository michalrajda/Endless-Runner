// Fill out your copyright notice in the Description page of Project Settings.


#include "VisiblitySwitcherButtonWidget.h"
#include "MainMenuHUD.h"
#include "Components/Button.h"

void UVisiblitySwitcherButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IsValid(Button))
	{
		Button->OnClicked.AddDynamic(this, &UVisiblitySwitcherButtonWidget::NotifyButtonClicked);
	}
}

void UVisiblitySwitcherButtonWidget::NotifyButtonClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AMainMenuHUD* HUD = PC->GetHUD<AMainMenuHUD>())
		{
			HUD->SwitchVisibility(WidgetTypeToSwitchVisibility);
		}
	}
}
