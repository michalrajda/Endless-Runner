// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetType.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None = 0 UMETA(HIDDEN),
	MainMenuButtons = 1 UMETA(DisplayName = "Main Menu Buttons"),
	Leaderboards = 2 UMETA(DispalyName = "Leaderboards"),
	KeyboardSettings = 3 UMETA(DisplayName = "Keayboard Settings"),
	EndLevelMessage = 4 UMETA(DisplayName = "Passing Level Message"),
	MagnetMessage = 5 UMETA(DisplayName = "Magnet Message"),
	PointsMultiplierMessage = 6 UMETA(DisplayName = "Points Multiplier Message")
};
