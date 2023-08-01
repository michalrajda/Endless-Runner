// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseButtonWidget.h"
#include "Components/TextBlock.h"

void UBaseButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (IsValid(ButtonText))
	{
		ButtonText->SetText(ButtonName);
	}
}
