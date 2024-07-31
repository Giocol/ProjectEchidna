// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCamera.h"

#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"
#include "ProjectEchidna/Character/MainCharacter.h"

void UThirdPersonCamera::ProcessCameraMovementInput(FVector2D input)                                                
{                                                                                                               
	//TODO: input: normalize? nah? ye? maybe clamp to max/min? fancy stuff!
	//TODO: swizzle input in controller?
	currentSphericalCoords.X += input.Y * 0.1;
	currentSphericalCoords.Y += input.X * 0.1; 
	currentSphericalCoords.X = FMath::Clamp(currentSphericalCoords.X, 0.1, 3.13); //avoid weird behavior at sphere's poles
}

void UThirdPersonCamera::CameraTick(float deltaTime)
{
	//SetWorldLocation(characterRef->GetActorLocation() - GetForwardVector() * 500)

	//this sucks! investigate why it freaks out when camera is right behind the player
	FVector2d interpSphericalCoords = PolarLerp(GetRelativeLocation().UnitCartesianToSpherical(), currentSphericalCoords, FMath::Clamp(deltaTime * 4, 0.f, 1.f));
	UE_LOG(LogTemp, Warning, TEXT("Interp is: %s (from %s to %s "), *interpSphericalCoords.ToString(), *GetRelativeLocation().UnitCartesianToSpherical().ToString(), *currentSphericalCoords.ToString());

	FVector newPos = interpSphericalCoords.SphericalToUnitCartesian() * neutralCameraOffset;
	
	//UE_LOG(LogTemp, Warning, TEXT("Polar coords in unit cart: %s"), *position.ToString());
	
	FRotator newRot = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), characterRef->GetActorLocation());
	
	SetWorldRotation(newRot);
	SetRelativeLocation(newPos);
}

FVector2d UThirdPersonCamera::PolarLerp(FVector2d current, FVector2d target, float alpha)
{
	//special function needed because it can overflow from 3.14 to -3.14 and vice versa
	float lerpedY = RadAngleLerp(current.Y, target.Y, alpha);
	
	//this is constrained already between 0.1 and 3.13!!!
	float lerpedX = FMath::Lerp(current.X, target.X, alpha);
	
	return FVector2D(lerpedX, lerpedY);
}

float UThirdPersonCamera::RadAngleLerp(float current, float target, float alpha)
{
	float delta = target - current;
	if (delta > PI) {
		delta -= 2*PI;
	} else if (delta < -PI) {
		delta += 2*PI;
	}
	return current + delta * alpha;
}
