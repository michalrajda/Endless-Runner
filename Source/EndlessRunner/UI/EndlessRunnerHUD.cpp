// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerHUD.h"
#include "EnterNameWidget.h"
#include "MessageWidget.h"

//Constructor for helper struct
FMessageProperties::FMessageProperties(UMessageWidget* InMessageWidget, AEndlessRunnerHUD* InHUD)
{
	if (IsValid(InMessageWidget) && IsValid(InHUD))
	{
		MessageWidget = InMessageWidget;
		TimerDelegate = FTimerDelegate::CreateUObject(InHUD, &AEndlessRunnerHUD::HideMessageWidget, MessageWidget->GetWidgetType());
	}
}

void AEndlessRunnerHUD::SetEnterNameWidget(UEnterNameWidget* InEnterNameWidget)
{
	if (IsValid(InEnterNameWidget))
	{
		if (IsValid(EnterNameWidget))
		{
			EnterNameWidget->RemoveFromParent();
		}
		EnterNameWidget = InEnterNameWidget;
	}
}

void AEndlessRunnerHUD::AddMessageWidget(UMessageWidget* InMessageWidget)
{
	if (IsValid(InMessageWidget))
	{
		EWidgetType InWidgetType = InMessageWidget->GetWidgetType();
		if (FMessageProperties* Message = Messages.Find(InWidgetType))
		{
				UMessageWidget* Widget = Message->MessageWidget;
				if (IsValid(Widget))
				{
					Widget->RemoveFromParent();
				}
				Message->MessageWidget = InMessageWidget;
		}
		else
		{
			Messages.Emplace(InWidgetType, FMessageProperties(InMessageWidget, this));
		}
	}
}

void AEndlessRunnerHUD::ShowMessageWidget(const EWidgetType MessageTypeToShow, const int32 FirstParamToShow, const int32 SecondParamToShow)
{
	if (UWorld* World = GetWorld())
	{
		if (FMessageProperties* Message = Messages.Find(MessageTypeToShow))
		{
			UMessageWidget* Widget = Message->MessageWidget;
			if (IsValid(Widget))
			{
				Widget->SetMessages(FirstParamToShow, SecondParamToShow);
				Widget->ChangeVisibility(true);
				World->GetTimerManager().SetTimer(Message->Timer, Message->TimerDelegate, Time, false);
			}
		}
	}
}

void AEndlessRunnerHUD::HideMessageWidget(const EWidgetType MessageTypeToHide)
{
	if (FMessageProperties* Message = Messages.Find(MessageTypeToHide))
	{
		UMessageWidget* Widget = Message->MessageWidget;
		if (IsValid(Widget))
		{
			Widget->ChangeVisibility(false);
		}
	}
}

void AEndlessRunnerHUD::ShowEnterNameWidget()
{
	if (IsValid(PlayerOwner) && IsValid(EnterNameWidget))
	{
		FInputModeUIOnly InputMode = FInputModeUIOnly();
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PlayerOwner->SetInputMode(InputMode);
		PlayerOwner->bShowMouseCursor = true;
		EnterNameWidget->ChangeVisibility(true);
	}
}

void AEndlessRunnerHUD::BeginPlay()
{
	Super::BeginPlay();
	CreateMenu();
}

void AEndlessRunnerHUD::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		FTimerManager& TM = World->GetTimerManager();
		for (TPair<EWidgetType, FMessageProperties>& Message : Messages)
		{
			FMessageProperties& M = Message.Value;
			M.MessageWidget = nullptr;
			TM.ClearTimer(M.Timer);
		}
	}
	if (IsValid(WidgetMenu))
	{
		WidgetMenu->RemoveFromParent();
		WidgetMenu = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void AEndlessRunnerHUD::CreateMenu()
{
	if (IsValid(WidgetClass) && IsValid(PlayerOwner))
	{
		if (WidgetMenu = CreateWidget<UUserWidget>(PlayerOwner, WidgetClass))
		{
			WidgetMenu->AddToViewport();
			PlayerOwner->SetInputMode(FInputModeGameOnly());
			if (UWorld* const World = GetWorld())
			{
				if (UGameViewportClient* const Viewport =  World->GetGameViewport())
				{
					Viewport->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
					Viewport->SetMouseLockMode(EMouseLockMode::LockAlways);
				}
			}
			PlayerOwner->bShowMouseCursor = false;
		}
	}
}