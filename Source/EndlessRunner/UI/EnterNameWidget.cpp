// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterNameWidget.h"
#include "Components/EditableText.h"
#include "EndlessRunnerHUD.h"
#include "EndlessRunnerGameInstance.h"

void UEnterNameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetVisibility(ESlateVisibility::Collapsed);
	if (IsValid(EditableText))
	{
		EditableText->OnTextCommitted.AddDynamic(this, &UEnterNameWidget::OnTextCommitted);
		APlayerController* PC = GetOwningPlayer();
		if (IsValid(PC))
		{
			if (AEndlessRunnerHUD* HUD = PC->GetHUD<AEndlessRunnerHUD>())
			{
				HUD->SetEnterNameWidget(this);
			}
		}
	}
}

void UEnterNameWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	FString Name;
	if (IsValid(EditableText))
	{
		if (CommitMethod == ETextCommit::OnEnter)
		{
			Name = Text.ToString();
			if (Name.Len() > MaxNameLength)
			{
				Name.LeftInline(MaxNameLength, true);
			}
		}
		EditableText->OnTextCommitted.Clear();
	}
	if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
	{
		APawn* Char = GetOwningPlayerPawn();
		GI->OpenMainMenu(Char, Name);
	}
}

void UEnterNameWidget::ChangeVisibility(bool bShouldBeVisible)
{
	ESlateVisibility NewVisibility = ESlateVisibility::Collapsed;
	if (IsValid(EditableText) && bShouldBeVisible)
	{
		NewVisibility = ESlateVisibility::SelfHitTestInvisible;
		EditableText->SetKeyboardFocus();
	}
	SetVisibility(NewVisibility);
}
