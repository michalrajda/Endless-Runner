// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseButtonWidget.h"
#include "EndGameButtonWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UEndGameButtonWidget : public UBaseButtonWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized() override;
};
