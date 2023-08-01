// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BoostType.h"
#include "WidgetType.h"
#include "EndlessRunnerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class ACollectible;

//delegates for communication with widgets
DECLARE_DELEGATE_TwoParams(FOnPlayerPickUpCoinSignature, int32/*CoinsNumber*/, int32/*Points*/)
DECLARE_DELEGATE_OneParam(FOnPlayerChangeDistanceSignature,int32/*DistanceInMeters*/)
DECLARE_DELEGATE_ThreeParams(FOnShowMessageChangeStateSignature, EWidgetType/*Message Type to show*/, int32, int32)

//Helper classes for attached boost's to Pawn
//Here we store timers, socket and attached boost
//We can specify how long boost will be active
UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced,Abstract)
class UCollectibleProperties : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<ACollectible> AttachedCollectible = nullptr;

	FTimerHandle Timer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float TimerRatio = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName SocketName = TEXT("Socket Name");

	virtual void SetTimer(ACollectible* InCollectible) {}

protected:

	virtual void EndTimer() {}
};

UCLASS()
class UMagnetAttachmentProperties : public UCollectibleProperties
{
	GENERATED_BODY()

public:

	virtual void SetTimer(ACollectible* InCollectible) override;

protected:

	virtual void EndTimer() override;
};

UCLASS()
class UMultiplierAttachmentProperties : public UCollectibleProperties
{
	GENERATED_BODY()

public:

	virtual void SetTimer(ACollectible* InCollectible) override;

protected:

	virtual void EndTimer() override;
};
//end of helper classes

UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AEndlessRunnerCharacter();

	void StartJump();

	//In tick we add movement in X direction and caclulate distance from start
	//We assume that start position is at X = 0.0f
	virtual void Tick(float DeltaTime) override;

	//We increase Max speed and grant points multiplied by Mulitplier, also here is displayed message
	void IncreaseMaxSpeed(const int32 PointsToAdd, const float DeltaSpeed);

	FORCEINLINE int32 GetPoints() const { return Points; }

	FORCEINLINE int32 GetCoins() const { return Coins; }

	FORCEINLINE int32 GetDistance() const { return Distance; }

	FORCEINLINE void AddCoin(const int32 PointsToAdd) 
	{ 
		Points += PointsToAdd * Multiplier;
		Coins += 1;
		OnPlayerPickUpCoin.ExecuteIfBound(Coins, Points);
	}

	FORCEINLINE void SetMultiplier(const int32 NewMultiplier) { Multiplier = NewMultiplier; }

	FORCEINLINE void SetDefaultMultiplier() { Multiplier = DefaultMultiplier; }

	FORCEINLINE void ShowMessageOnScreen(EWidgetType MessageType, const int32 FirstParamToShow, const int32 SecondParamToShow)
	{
		OnShowMessageChangeState.ExecuteIfBound(MessageType, FirstParamToShow, SecondParamToShow);
	}

	FORCEINLINE UCollectibleProperties* GetAttachedProperties(EBoostType Boost)
	{
		if (TObjectPtr<UCollectibleProperties>* Prop = AttachedCollectible.Find(Boost))
		{
			return *Prop;
		}
		return nullptr;
	}

	//Helper function to get controller casted to PlayerControllerClass
	template<typename PlayerControllerClass>
	FORCEINLINE PlayerControllerClass* GetPlayerController() { return Cast<PlayerControllerClass>(Controller); }

	FOnPlayerPickUpCoinSignature OnPlayerPickUpCoin;

	FOnPlayerChangeDistanceSignature OnPlayerChangeDistance;

	FOnShowMessageChangeStateSignature OnShowMessageChangeState;

protected:

	void Move(const FInputActionValue& Value);

	void SwapCrouch();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, noClear)
	TMap<EBoostType, TObjectPtr<UCollectibleProperties>> AttachedCollectible;

	int32 Points = 0;

	int32 Coins = 0;

	int32 Distance = 0;

	int32 Multiplier = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 DefaultMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Scale to apply when Distance is calculated. Distance = PawnLocation.X * DistanceScale. Pawn should start at X = 0.0f"))
	float DistanceScale = 0.01f;
};

