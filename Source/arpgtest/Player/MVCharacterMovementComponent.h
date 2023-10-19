// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MVCharacterMovementComponent.generated.h"

/**
 * For overriding protected members of [`UCharacterMovementComponent`].
 *
 * See https://forums.unrealengine.com/t/modify-nav-movement-attributes-in-c-on-ucharactermovementcomponent/106680/7
 * and https://forums.unrealengine.com/t/access-to-buseaccelerationforpaths-from-c/401046/4
 */
UCLASS()
class ARPGTEST_API UMVCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UMVCharacterMovementComponent();
};
