// Fill out your copyright notice in the Description page of Project Settings.


#include "ATopDownCharacter.h"

#include "MVCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

/// Constructor
///
/// We override the CharacterMovement component as we need to set [`bUseAccelerationForPaths`] to true, but it is
/// protected, so our custom MVCharacterMovementComponent sets it.  Acceleration needs to be turned on in order for
/// the released movement to work with default character blueprints (Manny/Quinn).
ATopDownCharacter::ATopDownCharacter(const class FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UMVCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction, allow independent free movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Skeletal Mesh translation and rotation to match capsule
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -95.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	// Configure character movement
	const auto MyCharacterMovement = GetCharacterMovement();
	MyCharacterMovement->bOrientRotationToMovement = true; // Rotate character to moving direction
	MyCharacterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	// Constrain movement to floor plane
	MyCharacterMovement->bConstrainToPlane = true;
	MyCharacterMovement->bSnapToPlaneAtStart = true;
	// General settings
	MyCharacterMovement->GravityScale = 1.5;
	MyCharacterMovement->MaxAcceleration = 1000.0;
	MyCharacterMovement->BrakingFrictionFactor = 1.0;
	MyCharacterMovement->BrakingDecelerationWalking = 1000.0;
	// Perching
	MyCharacterMovement->PerchRadiusThreshold = 20.0; // Stop player from getting too far off edge
	MyCharacterMovement->bUseFlatBaseForFloorChecks = true;
	// Check as if floor is flat instead of capsule to prevent lowering
	// Nav Movement
	// Match agent dimensions with capsule
	MyCharacterMovement->NavAgentProps.AgentRadius = 42.0;
	MyCharacterMovement->NavAgentProps.AgentHeight = 192.0;
	// Deceleration distance
	MyCharacterMovement->SetFixedBrakingDistance(200.0);

	// Camera boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	// Don't rotate spring arm
	SpringArm->SetRelativeRotation(FRotator(-60.0, 0.0, 0.0));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->TargetArmLength = 800.0f;
	// Don't pull in camera when colliding with level
	SpringArm->bDoCollisionTest = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; // Don't rotate relative to arm

	// TODO:
	// Clothing Simulation Factory
}
