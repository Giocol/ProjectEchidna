// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "ThirdPersonCamera.generated.h"

class AMainCharacter;

UCLASS()
class PROJECTECHIDNA_API UThirdPersonCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	void SetCharacterRef(AMainCharacter* ref) {characterRef = ref;}
	
	void ProcessCameraMovementInput(FVector2D input);

	void CameraTick(float deltaTime);

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float neutralCameraOffset = 100.f;

private:
	TObjectPtr<AMainCharacter> characterRef = nullptr;

	FVector2d targetSphericalCoords;

};
