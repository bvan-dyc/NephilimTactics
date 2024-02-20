// Copyright Epic Games, Inc. All Rights Reserved.

#include "NephPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/Actor/NephCameraActor.h"
#include "Engine/LocalPlayer.h"

ANephPlayerController::ANephPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ANephPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ANephPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ANephPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ANephPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ANephPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ANephPlayerController::OnSetDestinationReleased);
		
		// Setup keyboard / controller events
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ANephPlayerController::OnMoveForwardTriggered);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ANephPlayerController::OnMoveRightTriggered);
	}
}

void ANephPlayerController::OnInputStarted()
{
	StopMovement();
}

void ANephPlayerController::OnMoveForwardTriggered(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) { return; }

	ANephCameraActor* Camera = Cast<ANephCameraActor>(ControlledPawn);
	if (!Camera) { return; }

	Camera->MoveForward(InputActionValue.GetMagnitude());
}

void ANephPlayerController::OnMoveRightTriggered(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) { return; }

	ANephCameraActor* Camera = Cast<ANephCameraActor>(ControlledPawn);
	if (!Camera) { return; }

	Camera->MoveRight(InputActionValue.GetMagnitude());
}

// Triggered every frame when the input is held down
void ANephPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	const bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ANephPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);	}

	FollowTime = 0.f;
}
