// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseButtonWidget.h"
#include "WidgetType.h"
#include "VisiblitySwitcherButtonWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UVisiblitySwitcherButtonWidget : public UBaseButtonWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void NotifyButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "When we click button widget with this type will be displayed, in other case will be collapsed"))
	EWidgetType WidgetTypeToSwitchVisibility = EWidgetType::None;
};
