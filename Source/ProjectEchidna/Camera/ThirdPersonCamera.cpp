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
	//SetWorldLocation(characterRef->GetActorLocation() - GetForwardVector() * 500)

	FVector2d interpSphericalCoords = CameraUtils::PolarLerp(GetRelativeLocation().UnitCartesianToSpherical(), targetSphericalCoords, FMath::Clamp(deltaTime * 4, 0.f, 1.f));
	UE_LOG(LogTemp, Warning, TEXT("Interp is: %s (from %s to %s "), *interpSphericalCoords.ToString(), *GetRelativeLocation().UnitCartesianToSpherical().ToString(), *targetSphericalCoords.ToString());

	FVector newPos = interpSphericalCoords.SphericalToUnitCartesian() * neutralCameraOffset;
	
	//UE_LOG(LogTemp, Warning, TEXT("Polar coords in unit cart: %s"), *position.ToString());
	
	FRotator newRot = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), characterRef->GetActorLocation());
	
	SetWorldRotation(newRot);
	SetRelativeLocation(newPos);
}
