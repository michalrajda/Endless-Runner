// Fill out your copyright notice in the Description page of Project Settings.


#include "VisibilitySwitcherWidget.h"
#include "MainMenuHUD.h"

void UVisibilitySwitcherWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AMainMenuHUD* HUD = PC->GetHUD<AMainMenuHUD>())
		{
			HUD->OnVisibilityElementsChangeState.AddUObject(this, &UVisibilitySwitcherWidget::SwitchVisibility);
		}
	}
}

void UVisibilitySwitcherWidget::SwitchVisibility(EWidgetType WidgetTypeToSwitchVisibility)
{
	if (WidgetTypeToSwitchVisibility == WidgetType)
	{
		if (GetVisibility() == ESlateVisibility::Collapsed)
		{
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		if (GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
