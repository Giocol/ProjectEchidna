// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCamera.h"

#include "Kismet/KismetMathLibrary.h"
#include "ProjectEchidna/Character/MainCharacter.h"
#include "ProjectEchidna/Utils/CameraUtils.h"

void UThirdPersonCamera::ProcessCameraMovementInput(FVector2D input)                                                
{
	if(!canAutoAlign) //gets called if an autoalignment is currently happening, allows to get out of it on input avoiding camera jerks
		targetSphericalCoords = GetRelativeLocation().UnitCartesianToSpherical();
	
	//TODO: input: normalize? nah? ye? maybe clamp to max/min?
	//TODO: swizzle input in controller?
	targetSphericalCoords.X += input.Y * 0.05; //TODO: hardcoded value out, sens in.
	targetSphericalCoords.Y += input.X * 0.05;

	//avoid weird behavior at sphere's poles
	targetSphericalCoords.X = FMath::Clamp(targetSphericalCoords.X, pitchLowerLimitRads, pitchUpperLimitRads); 

	targetFov = FMath::Lerp(wormsEyeCameraFOV, birdsEyeCameraFOV, 1 - targetSphericalCoords.X / pitchUpperLimitRads); //TODO: THIS VALUE SHOULD BE 3.13! Change the range of X	targetFov = FMath::Lerp(wormsEyeCameraFOV, birdsEyeCameraFOV, 1 - targetSphericalCoords.X / 2.13); //TODO: THIS VALUE SHOULD BE 3.13! Change the range of X
	targetOffset = FMath::Lerp(wormsEyeCameraOffset, birdsEyeCameraOffset, 1 - targetSphericalCoords.X / pitchUpperLimitRads);//TODO: THIS VALUE SHOULD BE 3.13! Change the range of X

	timeSinceLastInput = 0.f;
	currentPolarPostionInterpSpeed = polarPositionInterpSpeed;

	canAutoAlign = true;
}

void UThirdPersonCamera::BeginPlay() {
	Super::BeginPlay();

	SetRelativeLocation(FVector2d(startingPitch, startingYaw).SphericalToUnitCartesian() * startingOffset);

	targetOffset = startingOffset;
	targetFov = startingFov;
	SetFieldOfView(targetFov);
	canAutoAlign = false; //avoid autoaligning behavior until the first input
}

void UThirdPersonCamera::CameraTick(float deltaTime)
{
	UpdateCameraPosition(deltaTime);
	UpdateCameraRotation(deltaTime);
	UpdateCameraOffset(deltaTime);
	UpdateFOV(deltaTime);
	if(doesAutoAlign)
		UpdateAutoAlignment(deltaTime);
}

void UThirdPersonCamera::UpdateCameraPosition(float deltaTime)
{
	const FVector2d interpSphericalCoords =
		CameraUtils::PolarLerp(
			GetRelativeLocation().UnitCartesianToSpherical(),
			targetSphericalCoords,
			FMath::Clamp(deltaTime * currentPolarPostionInterpSpeed, 0.f, 1.f));
	//UE_LOG(LogTemp, Warning, TEXT("Interp is: %s (from %s to %s "), *interpSphericalCoords.ToString(), *GetRelativeLocation().UnitCartesianToSpherical().ToString(), *targetSphericalCoords.ToString());
	SetRelativeLocation(interpSphericalCoords.SphericalToUnitCartesian() * currentOffset);
}

void UThirdPersonCamera::UpdateCameraRotation(float deltaTime)
{
	FRotator newRot = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), characterRef->GetActorLocation());
	SetWorldRotation(newRot);
}

void UThirdPersonCamera::UpdateFOV(float deltaTime)
{
	currentFov = FMath::FInterpTo(currentFov, targetFov, deltaTime, offsetInterpSpeed);
	SetFieldOfView(currentFov);
}

void UThirdPersonCamera::UpdateCameraOffset(float deltaTime)
{
	currentOffset = FMath::FInterpTo(currentOffset, targetOffset, deltaTime, fovInterpSpeed);
}

void UThirdPersonCamera::UpdateAutoAlignment(float deltaTime)
{
	timeSinceLastInput+=deltaTime;

	if(timeSinceLastInput >= autoAlignmentCooldown && canAutoAlign)
	{
		targetSphericalCoords.X = 1;
		targetSphericalCoords.Y = characterRef->GetMeshComponentPolarYaw();
		currentPolarPostionInterpSpeed = autoAlignmentInterpSpeed;
		canAutoAlign = false;
	}
}
