// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetType.h"
#include "EndlessRunnerHUD.generated.h"

class UUserWidget;
class UEnterNameWidget;
class UMessageWidget;

//Helper struct for storing message and timer
USTRUCT(BlueprintType)
struct FMessageProperties
{
	GENERATED_BODY()

public:

	FMessageProperties(UMessageWidget* InMessageWidget = nullptr, AEndlessRunnerHUD* InHUD = nullptr);

	FTimerHandle Timer;

	FTimerDelegate TimerDelegate;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UMessageWidget> MessageWidget = nullptr;
};
//

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerHUD : public AHUD
{
	GENERATED_BODY()

public:

	void SetEnterNameWidget(UEnterNameWidget* InEnterNameWidget);

	void AddMessageWidget(UMessageWidget* InMessageWidget);

	//Usage:
	//In Magnet and PointsMultiplier FirstParameter describe Boost Property and second how long boost is active
	//In EndLevel firt parameter describe how many points we got and second how many speed will be added
	void ShowMessageWidget(const EWidgetType MessageTypeToShow, const int32 FirstParamToShow, const int32 SecondParamToShow);

	void ShowEnterNameWidget();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void CreateMenu();

	void HideMessageWidget(const EWidgetType MessageTypeToHide);

	UPROPERTY(EditDefaultsOnly, noClear)
	TSubclassOf<UUserWidget> WidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TObjectPtr<UUserWidget> WidgetMenu = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TObjectPtr<UEnterNameWidget> EnterNameWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TMap<EWidgetType, FMessageProperties> Messages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Time for displaying messages."))
	float Time = 3.0f;

	friend FMessageProperties;
};
