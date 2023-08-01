// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TurtleAnimInstance.generated.h"

class AEndlessRunnerCharacter;
class UCharacterMovementComponent;

UCLASS()
class ENDLESSRUNNER_API UTurtleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<AEndlessRunnerCharacter> Character = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float MinVelocityTreshold = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	float MinVelocityForJumping = 100.0f;

	float MaxSpeed = 1.0f;

	FVector Velocity;

	FVector Acceleration;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly)
	bool bIsFalling = false;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly)
	bool bIsJumping = false;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly)
	float AlfaSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly)
	bool bIsCrouching = false;
};
