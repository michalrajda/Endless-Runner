// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SaveGameProperties.generated.h"

//Helper struct for keeping data together
USTRUCT(BlueprintAble)
struct FSaveGameProperties
{
	GENERATED_BODY()

public:

	FSaveGameProperties(const FString& InName = TEXT(""), int32 InPoints = 0, int32 InCoins = 0, int32 InDistance = 0) : Name( InName ), Points( InPoints ), Coins( InCoins ), Distance( InDistance ) {}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Points;

	UPROPERTY()
	int32 Coins;

	UPROPERTY()
	int32 Distance;
};

FORCEINLINE bool operator<(const FSaveGameProperties& Left, const FSaveGameProperties& Right)
{
	if (Left.Points > Right.Points)
	{
		return true;
	}
	else if (Left.Points == Right.Points)
	{
		if (Left.Coins > Right.Coins)
		{
			return true;
		}
		else if (Left.Coins == Right.Coins)
		{
			if (Left.Distance > Right.Distance)
			{
				return true;
			}
		}
	}
	return false;
}