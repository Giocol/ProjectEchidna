﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	virtual void BeginPlay() override;
	void CameraTick(float deltaTime);

private:
	void UpdateCameraPosition(float deltaTime);
	void UpdateCameraRotation(float deltaTime);
	void UpdateFOV(float deltaTime);
	void UpdateCameraOffset(float deltaTime);
	void UpdateAutoAlignment(float deltaTime);

	void ComputeFov();
	void ComputeOffset();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float polarPositionInterpSpeed = 4.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Starting")
	float startingPitch = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Starting")
	float startingYaw = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Starting")
	float startingOffset = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Starting")
	float startingFov = 90.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Offsets")
	float birdsEyeCameraOffset = 800.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Offsets")
	float wormsEyeCameraOffset = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Offsets")
	float offsetInterpSpeed = 2.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | FOV")
	float birdsEyeCameraFOV = 70.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | FOV")
	float wormsEyeCameraFOV = 120.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | FOV")
	float fovInterpSpeed = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Pitch")
	float pitchLowerLimitRads = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Pitch")
	float pitchUpperLimitRads = 1.90f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Alignment")
	float autoAlignmentCooldown = 8.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Alignment")
	float autoAlignmentInterpSpeed = .2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings | Alignment")
	bool doesAutoAlign = true;

private:
	TObjectPtr<AMainCharacter> characterRef = nullptr;
	
	FVector2d targetSphericalCoords = FVector2d(1.f, 0.f);
	float targetOffset;
	float targetFov;

	float timeSinceLastInput = 0.f;
	bool canAutoAlign = true;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera Settings | Debug")
	float currentOffset = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "Camera Settings | Debug")
	float currentFov = 90.f;

	UPROPERTY(VisibleAnywhere, Category = "Camera Settings | Debug")
	float currentPolarPostionInterpSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Camera Settings | Debug")
	float currentFovInterpSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Camera Settings | Debug")
	float currentOffsetInterpSpeed;

};
