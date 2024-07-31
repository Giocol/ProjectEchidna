#include "MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectEchidna/Camera/ThirdPersonCamera.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraRef = CreateDefaultSubobject<UThirdPersonCamera>("MainCamera");
	cameraRef->SetupAttachment(GetCapsuleComponent());

	cameraRef->SetCharacterRef(this);
}

void AMainCharacter::ProcessCharacterMovementInput(FVector2D input)
{
	AddMovementInput(GetActorForwardVector(), input.X);
	AddMovementInput(GetActorRightVector(), input.Y);
}

void AMainCharacter::ProcessCameraMovementInput(FVector2D input)
{
	if(cameraRef)
		cameraRef->ProcessCameraMovementInput(input);
}

void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	cameraRef->CameraTick(deltaTime);
}
