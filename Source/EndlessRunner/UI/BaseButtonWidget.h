// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseButtonWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class ENDLESSRUNNER_API UBaseButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonText = nullptr;

	UPROPERTY(EditAnywhere)
	FText ButtonName = FText::FromString(TEXT("ButtonName"));
};
