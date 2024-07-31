// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCamera.h"

#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"
#include "ProjectEchidna/Character/MainCharacter.h"
#include "ProjectEchidna/Utils/CameraUtils.h"

void UThirdPersonCamera::ProcessCameraMovementInput(FVector2D input)                                                
{                                                                                                               
	//TODO: input: normalize? nah? ye? maybe clamp to max/min?
	//TODO: swizzle input in controller?
	targetSphericalCoords.X += input.Y * 0.1; //TODO: hardcoded value out, sens in.
	targetSphericalCoords.Y += input.X * 0.1; 
	targetSphericalCoords.X = FMath::Clamp(targetSphericalCoords.X, 0.1, 3.13); //avoid weird behavior at sphere's poles
}

void UThirdPersonCamera::CameraTick(float deltaTime)
{
	UpdateCameraPosition(deltaTime);
	UpdateCameraRotation(deltaTime);
	UpdateCameraOffset(deltaTime);
	UpdateFOV(deltaTime);
}

void UThirdPersonCamera::UpdateCameraPosition(float deltaTime)
{
	const FVector2d interpSphericalCoords = CameraUtils::PolarLerp(GetRelativeLocation().UnitCartesianToSpherical(), targetSphericalCoords, FMath::Clamp(deltaTime * 4, 0.f, 1.f));
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
	currentFov = FMath::Lerp(wormsEyeCameraFOV, birdsEyeCameraFOV, 1 - targetSphericalCoords.X / 2.13); //TODO: THIS VALUE SHOULD BE 3.13! Change the range of X
	SetFieldOfView(currentFov);
	UE_LOG(LogTemp, Warning, TEXT("FOV: %f"), FieldOfView);
}

void UThirdPersonCamera::UpdateCameraOffset(float deltaTime)
{
	currentOffset = FMath::Lerp(wormsEyeCameraOffset, birdsEyeCameraOffset, 1 - targetSphericalCoords.X / 2.13);//TODO: THIS VALUE SHOULD BE 3.13! Change the range of X
}
