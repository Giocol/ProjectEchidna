// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainCharacter.h"
#include "ProjectEchidna/Camera/ThirdPersonCamera.h"

void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();
}

void AThirdPersonController::OnPossess(APawn* InPawn)
{
	characterRef = Cast<AMainCharacter>(InPawn);
	checkf(characterRef, TEXT("Missing AMainCharacter OnPosses"));

	
	inputSubsystemRef = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	checkf(inputSubsystemRef, TEXT("missing UEnhancedInputLocalPlayerSubsystem OnPosses"))

	inputComponentRef = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(inputSubsystemRef, TEXT("missing UEnhancedInputComponent OnPosses"))

	SetupInputMappingContext();
	SetupInputActions();
	Super::OnPossess(InPawn);
}

void AThirdPersonController::OnUnPossess()
{
	Super::OnUnPossess();
}


void AThirdPersonController::SetupInputMappingContext()
{
	inputSubsystemRef->ClearAllMappings();
	inputSubsystemRef->AddMappingContext(thirdPersonContext, 0);
}

void AThirdPersonController::SetupInputActions()
{
	if(!characterMovementAction)
		UE_LOG(LogTemp, Error, TEXT("Missing character movement action ref! Please plug it in the ThirdPersonControllerBP!"));
	
	if(!cameraMovementAction)
		UE_LOG(LogTemp, Error, TEXT("Missing camera movement action ref! Please plug it in the ThirdPersonControllerBP!"));
	
	inputComponentRef->BindAction(characterMovementAction, ETriggerEvent::Triggered, this, &AThirdPersonController::HandleMovement);
	inputComponentRef->BindAction(cameraMovementAction, ETriggerEvent::Triggered, this, &AThirdPersonController::HandleCameraMovement);
}

void AThirdPersonController::HandleMovement(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Movement input: %f, %f"), axis.X, axis.Y);
	characterRef->ProcessCharacterMovementInput(axis);
}

void AThirdPersonController::HandleCameraMovement(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Camera input: %f, %f"), axis.X, axis.Y);
	characterRef->ProcessCameraMovementInput(axis);
}

