// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::SwitchVisibility(const EWidgetType WidgetToSwitchVisibility)
{
	OnVisibilityElementsChangeState.Broadcast(WidgetToSwitchVisibility);
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	CreateMenu();
}

void AMainMenuHUD::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(WidgetMenu))
	{
		WidgetMenu->RemoveFromParent();
		WidgetMenu = nullptr;
	}
	OnVisibilityElementsChangeState.Clear();
	Super::EndPlay(EndPlayReason);
}

void AMainMenuHUD::CreateMenu()
{
	if (IsValid(WidgetClass) && IsValid(PlayerOwner))
	{
		if (WidgetMenu = CreateWidget<UUserWidget>(PlayerOwner, WidgetClass))
		{
			WidgetMenu->AddToViewport();
			FInputModeUIOnly InputMode = FInputModeUIOnly();
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerOwner->SetInputMode(FInputModeUIOnly());
			if (UWorld* const World = GetWorld())
			{
				if (UGameViewportClient* const Viewport = World->GetGameViewport())
				{
					Viewport->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
				}
			}
			PlayerOwner->bShowMouseCursor = true;
		}
	}
}
