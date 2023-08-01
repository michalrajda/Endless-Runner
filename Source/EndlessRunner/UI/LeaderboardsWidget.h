// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilitySwitcherWidget.h"
#include "LeaderboardsWidget.generated.h"

class UScrollBox;
class ULeaderboardsSlotWidget;

UCLASS()
class ENDLESSRUNNER_API ULeaderboardsWidget : public UVisibilitySwitcherWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

#if WITH_EDITOR
	virtual void NativePreConstruct() override;
#endif

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScrollBox> LeaderboardsContainer = nullptr;
	
	UPROPERTY(EditAnywhere, noClear)
	TSubclassOf<ULeaderboardsSlotWidget> SlotClass = nullptr;

	UPROPERTY(EditAnywhere)
	FMargin SlotPadding = FMargin(15.0f);

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EHorizontalAlignment> SlotHorizontalAligment = EHorizontalAlignment::HAlign_Fill;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EVerticalAlignment> SlotVerticalAligment = EVerticalAlignment::VAlign_Fill;

//it's only for designer purpose, in shipped version should be removed
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	int32 MaxSlots = 10;

	UPROPERTY()
	bool bShouldDoPreConstruct = true;

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<TObjectPtr<ULeaderboardsSlotWidget>> LeaderboardSlots;
#endif
};
