// Fill out your copyright notice in the Description page of Project Settings.


#include "ATopDownPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

DEFINE_LOG_CATEGORY(LogTopDownCharacter);

ATopDownPlayerController::ATopDownPlayerController()
{
	Destination = FVector::Zero();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Fetch data assets from default locations if available
	// https://forums.unrealengine.com/t/how-to-get-my-dataasset-in-c/144472/11
	if (const ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingAsset(TEXT("/Game/Input/IMC_Default"))
		; InputMappingAsset.Succeeded())
	{
		InputMapping = InputMappingAsset.Object;
	}
	if (const ConstructorHelpers::FObjectFinder<UInputAction> SetDestinationActionAsset(
		TEXT("/Game/Input/IA_SetDestinationAction")); SetDestinationActionAsset.Succeeded())
	{
		SetDestinationAction = SetDestinationActionAsset.Object;
	}
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(SetDestinationAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnSetDestinationStarted);
		Input->BindAction(SetDestinationAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnSetDestinationTriggered);
		Input->BindAction(SetDestinationAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnSetDestinationReleased);
		Input->BindAction(SetDestinationAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTopDownCharacter, Error,
		       TEXT("'%s' Failed to find EnhancedInputComponent!  The legacy system is not currently supported"),
		       *GetNameSafe(this));
	}
}

void ATopDownPlayerController::OnSetDestinationStarted()
{
	// Stop any previous movement
	StopMovement();
}

void ATopDownPlayerController::OnSetDestinationTriggered()
{
	// We look for the location in the world where the player has pressed the input
	// Trace from cursor position, and update Destination if it's in a visible position
	if (FHitResult Hit; GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Destination = Hit.Location;
	}

	// Move in direction of Destination
	if (const auto ControlledPawn = GetPawn())
	{
		const FVector Direction = (Destination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(Direction, 1.0, false);
	}
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	// AI helper to move player to destination
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
}
