// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnterNameWidget.generated.h"

class UEditableText;

UCLASS()
class ENDLESSRUNNER_API UEnterNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ChangeVisibility(bool bShouldBeVisible);
	
protected:

	virtual void NativeOnInitialized();

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableText> EditableText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxNameLength = 35;
};
