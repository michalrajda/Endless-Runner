// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetType.h"
#include "VisibilitySwitcherWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UVisibilitySwitcherWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;
	
	void SwitchVisibility(EWidgetType WidgetTypeToSwitchVisibility);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWidgetType WidgetType = EWidgetType::None;
};
