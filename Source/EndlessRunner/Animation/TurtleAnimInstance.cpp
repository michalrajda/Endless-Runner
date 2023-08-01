// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleAnimInstance.h"
#include "EndlessRunnerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTurtleAnimInstance::NativeInitializeAnimation()
{
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(GetOwningActor()))
	{
		Character = Char;
		MovementComponent = Char->GetCharacterMovement();
	}
}

void UTurtleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(Character))
	{
		MaxSpeed = MovementComponent->MaxWalkSpeed;
		Velocity = MovementComponent->Velocity;
		Acceleration = MovementComponent->GetCurrentAcceleration();
		bIsFalling = MovementComponent->IsFalling();
		bIsCrouching = Character->bIsCrouched;
	}
}

void UTurtleAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(Character))
	{
		const float GroundSpeed = Velocity.Size2D();
		AlfaSpeed = GroundSpeed / MaxSpeed;
		bShouldMove = (GroundSpeed > MinVelocityTreshold) && (!Acceleration.IsZero());
		bIsJumping = (Velocity.Z > MinVelocityForJumping) && bIsFalling;
	}
}
