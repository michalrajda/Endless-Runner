// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetType.h"
#include "MainMenuHUD.generated.h"

class UUserWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityElementsChangeStateSignature, EWidgetType)

UCLASS()
class ENDLESSRUNNER_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	void SwitchVisibility(const EWidgetType WidgetToSwitchVisibility);

	FOnVisibilityElementsChangeStateSignature OnVisibilityElementsChangeState;
	
protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void CreateMenu();

	UPROPERTY(EditDefaultsOnly, noClear)
	TSubclassOf<UUserWidget> WidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UUserWidget> WidgetMenu = nullptr;
};
