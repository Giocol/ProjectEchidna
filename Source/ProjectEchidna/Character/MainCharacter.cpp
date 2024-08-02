#include "MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectEchidna/Camera/ThirdPersonCamera.h"
#include "Components/SkeletalMeshComponent.h"

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
	targetDirection = meshComponent->GetForwardVector() * input.X;
	targetDirection += meshComponent->GetRightVector() * input.Y;
	//AddMovementInput(targetDirection);
	
	AddMovementInput(meshComponent->GetForwardVector(), input.X);
	AddMovementInput(meshComponent->GetRightVector(), input.Y);
	
	//targetDirection = FVector(input.X, input.Y, 0); //inefficient?
}

void AMainCharacter::ProcessCameraMovementInput(FVector2D input)
{
	if(cameraRef)
		cameraRef->ProcessCameraMovementInput(input);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	targetDirection = GetActorForwardVector();
	meshComponent = GetMesh();
}

void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	cameraRef->CameraTick(deltaTime);
	meshComponent->SetWorldRotation(FMath::RInterpTo(meshComponent->GetComponentRotation(), targetDirection.Rotation(), deltaTime, 10));
}
