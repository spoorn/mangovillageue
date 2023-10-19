// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATopDownPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

DECLARE_LOG_CATEGORY_EXTERN(LogTopDownCharacter, Log, All);

/**
 * Top Down player controller
 */
UCLASS()
class ARPGTEST_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownPlayerController();

	virtual void BeginPlay() override;

	/// Handle input to movement
	virtual void SetupInputComponent() override;

	/// Input Mapping Context to map keys -> actions.  Defaults to asset at "/Game/Input/IMC_Default"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* InputMapping;

	/// Set player destination Input Action.  Defaults to asset at "/Game/Input/IA_SetDestinationAction"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* SetDestinationAction;

protected:
	/// Current destination
	FVector Destination;

	/** Input handlers for SetDestinationAction */

	/// When SetDestination starts
	void OnSetDestinationStarted();
	/// While SetDestination is actioning
	void OnSetDestinationTriggered();
	/// When SetDestination is released
	void OnSetDestinationReleased();
};
