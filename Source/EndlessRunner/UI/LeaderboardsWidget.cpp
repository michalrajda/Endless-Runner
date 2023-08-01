// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardsWidget.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "LeaderboardsSlotWidget.h"
#include "SaveGameProperties.h"
#include "EndlessRunnerGameInstance.h"

void ULeaderboardsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
#if WITH_EDITOR && WITH_EDITORONLY_DATA
	if (!LeaderboardSlots.IsEmpty())
	{
		for (TObjectPtr<ULeaderboardsSlotWidget>& SlotWidget : LeaderboardSlots)
		{
			if (IsValid(SlotWidget))
			{
				SlotWidget->RemoveFromParent();
			}
		}
		LeaderboardSlots.Empty();
	}
#endif
	if (IsValid(SlotClass) && IsValid(LeaderboardsContainer))
	{
		if (UEndlessRunnerGameInstance* GI = GetGameInstance<UEndlessRunnerGameInstance>())
		{
			const TArray<FSaveGameProperties>& LeaderboardProperties = GI->GetLeaderboardList();
			int32 Position = 1;
			for (const FSaveGameProperties& SlotProperites : LeaderboardProperties)
			{
				if (ULeaderboardsSlotWidget* SlotWidget = CreateWidget<ULeaderboardsSlotWidget>(this, SlotClass))
				{
					if (UScrollBoxSlot* BoxSlot = Cast<UScrollBoxSlot>(LeaderboardsContainer->AddChild(SlotWidget)))
					{
						BoxSlot->SetHorizontalAlignment(SlotHorizontalAligment);
						BoxSlot->SetVerticalAlignment(SlotVerticalAligment);
						BoxSlot->SetPadding(SlotPadding);
						SlotWidget->SetPropertiesInSlot(SlotProperites, Position);
						Position++;
#if WITH_EDITOR && WITH_EDITORONLY_DATA
						LeaderboardSlots.Emplace(SlotWidget);
#endif
					}
				}
			}
#if WITH_EDITOR && WITH_EDITORONLY_DATA
			bShouldDoPreConstruct = false;
#endif
		}
	}
}

#if WITH_EDITOR
void ULeaderboardsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
#if WITH_EDITORONLY_DATA
	if (IsValid(SlotClass) && IsValid(LeaderboardsContainer) && bShouldDoPreConstruct)
	{
		FSaveGameProperties SlotProperites;
		for (TObjectPtr<ULeaderboardsSlotWidget>& SlotWidget : LeaderboardSlots)
		{
			if (IsValid(SlotWidget))
			{
				SlotWidget->RemoveFromParent();
			}
		}
		LeaderboardSlots.Empty();
		for (int32 Index = 1; Index <= MaxSlots; Index++)
		{
			if (ULeaderboardsSlotWidget* SlotWidget = CreateWidget<ULeaderboardsSlotWidget>(this, SlotClass))
			{
				if (UScrollBoxSlot* BoxSlot = Cast<UScrollBoxSlot>(LeaderboardsContainer->AddChild(SlotWidget)))
				{
					BoxSlot->SetHorizontalAlignment(SlotHorizontalAligment);
					BoxSlot->SetVerticalAlignment(SlotVerticalAligment);
					BoxSlot->SetPadding(SlotPadding);
					SlotWidget->SetPropertiesInSlot(SlotProperites, Index);
					LeaderboardSlots.Emplace(SlotWidget);
				}
			}
		}
	}
#endif
}
#endif
