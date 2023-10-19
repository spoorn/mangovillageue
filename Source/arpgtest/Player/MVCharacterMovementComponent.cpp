// Fill out your copyright notice in the Description page of Project Settings.


#include "MVCharacterMovementComponent.h"

UMVCharacterMovementComponent::UMVCharacterMovementComponent()
{
	// Need to set acceleration for pathing to get the default UE character animations working with released movement.
	bUseAccelerationForPaths = true;
}
