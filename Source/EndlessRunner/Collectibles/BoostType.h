// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoostType.generated.h"

UENUM(BlueprintType)
enum class EBoostType : uint8
{
	None = 0 UMETA(HIDDEN),
	Magnet = 1 UMETA(DisplayName = "Magnet"),
	PointsMultiplier = 2 UMETA(DispalyName = "PointsMultiplier")
};
