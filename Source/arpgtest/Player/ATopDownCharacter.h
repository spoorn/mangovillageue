// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATopDownCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Default top down character.
 */
UCLASS()
class ARPGTEST_API ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/// Sets default values for this character's properties
	/// We access the ObjectInitializer as in the super constructor so we can initialize with our own custom
	/// MVCharacterMovementComponent to set some protected values.
	explicit ATopDownCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/// Camera boom component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SpringArm")
	USpringArmComponent* SpringArm;

	/// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* Camera;
};
