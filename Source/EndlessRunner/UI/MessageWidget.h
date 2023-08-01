// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetType.h"
#include "MessageWidget.generated.h"

class UTextBlock;

UCLASS()
class ENDLESSRUNNER_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FORCEINLINE void ChangeVisibility(bool bShouldBeVisible)
	{
		ESlateVisibility NewVisibility = bShouldBeVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
		SetVisibility(NewVisibility);
	}

	FORCEINLINE EWidgetType GetWidgetType() const { return WidgetType; }

	//Usage:
	//In Magnet and PointsMultiplier FirstParameter describe Boost Property and second how long boost is active
	//In EndLevel firt parameter describe how many points we got and second how many speed will be added
	void SetMessages(const int32 FirstParamToShow, const int32 SecondParamToShow);

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText1 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWidgetType WidgetType = EWidgetType::None;
};
