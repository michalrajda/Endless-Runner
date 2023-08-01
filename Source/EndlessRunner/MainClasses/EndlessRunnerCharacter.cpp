// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Collectible.h"
#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerHUD.h"


void UMagnetAttachmentProperties::SetTimer(ACollectible* InCollectible)
{
	AttachedCollectible = InCollectible;
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(GetOuter()))
	{
		Char->ShowMessageOnScreen(EWidgetType::MagnetMessage, InCollectible->GetCollectibleProperty(), TimerRatio);
		if (UWorld* World = Char->GetWorld())
		{
			World->GetTimerManager().SetTimer(Timer, this, &UMagnetAttachmentProperties::EndTimer, TimerRatio, false);
		}
	}
}

void UMagnetAttachmentProperties::EndTimer()
{
	if (IsValid(AttachedCollectible))
	{
		AttachedCollectible->Destroy();
	}
}

void UMultiplierAttachmentProperties::SetTimer(ACollectible* InCollectible)
{
	AttachedCollectible = InCollectible;
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(GetOuter()))
	{
		Char->ShowMessageOnScreen(EWidgetType::PointsMultiplierMessage, InCollectible->GetCollectibleProperty(), TimerRatio);
		if (UWorld* World = Char->GetWorld())
		{
			World->GetTimerManager().SetTimer(Timer, this, &UMultiplierAttachmentProperties::EndTimer, TimerRatio, false);
		}
	}
}

void UMultiplierAttachmentProperties::EndTimer()
{
	if (IsValid(AttachedCollectible))
	{
		AttachedCollectible->Destroy();
	}
	if (AEndlessRunnerCharacter* Char = Cast<AEndlessRunnerCharacter>(GetOuter()))
	{
		Char->SetDefaultMultiplier();
	}
}

AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(26.0f, 55.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	CharMovement->bOrientRotationToMovement = true;
	CharMovement->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	CharMovement->JumpZVelocity = 500.f;
	CharMovement->AirControl = 0.35f;
	CharMovement->MaxWalkSpeed = 500.f;
	CharMovement->MaxWalkSpeedCrouched = 500.0f;
	CharMovement->MinAnalogWalkSpeed = 20.f;
	CharMovement->BrakingDecelerationWalking = 2000.f;
	CharMovement->NavAgentProps.bCanCrouch = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	SetDefaultMultiplier();
}

void AEndlessRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(FVector::ForwardVector);
	if (IsValid(RootComponent))
	{
		const int32 NewDistance = static_cast<int32>(RootComponent->GetComponentTransform().GetTranslation().X * DistanceScale);
		if (NewDistance > Distance)
		{
			Distance = NewDistance;
			OnPlayerChangeDistance.ExecuteIfBound(Distance);
		}
	}
}

void AEndlessRunnerCharacter::IncreaseMaxSpeed(const int32 PointsToAdd, const float DeltaSpeed)
{
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (IsValid(CharMovement))
	{
		CharMovement->MaxWalkSpeed += DeltaSpeed;
		CharMovement->MaxWalkSpeedCrouched += DeltaSpeed;
	}
	const int32 DeltaPoints = PointsToAdd * Multiplier;
	Points += DeltaPoints;
	ShowMessageOnScreen(EWidgetType::EndLevelMessage, DeltaPoints, DeltaSpeed);
	OnPlayerPickUpCoin.ExecuteIfBound(Coins, Points);
}

void AEndlessRunnerCharacter::BeginPlay()
{ 
	Super::BeginPlay();
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if(IsValid(CharMovement))
	{
		CharMovement->MaxWalkSpeedCrouched = CharMovement->MaxWalkSpeed;
	}
	if (APlayerController* PC = GetPlayerController<APlayerController>())
	{
		if (AEndlessRunnerHUD* HUD = PC->GetHUD<AEndlessRunnerHUD>())
		{
			OnShowMessageChangeState.BindUObject(HUD, &AEndlessRunnerHUD::ShowMessageWidget);
		}
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AEndlessRunnerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		FTimerManager& TM = World->GetTimerManager();
		for (const TPair<EBoostType,TObjectPtr<UCollectibleProperties>>& Collectible: AttachedCollectible)
		{
			UCollectibleProperties* Prop = Collectible.Value;
			if (IsValid(Prop))
			{
				TM.ClearTimer(Prop->Timer);
			}
		}
	}
	OnPlayerPickUpCoin.Unbind();
	OnPlayerChangeDistance.Unbind();
	OnShowMessageChangeState.Unbind();
	Super::EndPlay(EndPlayReason);
}

void AEndlessRunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEndlessRunnerCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEndlessRunnerCharacter::Move);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEndlessRunnerCharacter::SwapCrouch);
	}
}

void AEndlessRunnerCharacter::StartJump()
{
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (IsValid(CharMovement))
	{
		if (bIsCrouched)
		{
			CharMovement->bWantsToCrouch = false;
		}
		else
		{
			Jump();
		}
	}
}

void AEndlessRunnerCharacter::Move(const FInputActionValue& Value)
{
	const float MovementRightDirection = Value.Get<float>();
	AddMovementInput(FVector::RightVector, MovementRightDirection);
}

void AEndlessRunnerCharacter::SwapCrouch()
{
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (IsValid(CharMovement))
	{
		if (bIsCrouched)
		{
			CharMovement->bWantsToCrouch = false;
		}
		else if(!CharMovement->IsFalling())
		{
			CharMovement->bWantsToCrouch = true;
		}
	}
}