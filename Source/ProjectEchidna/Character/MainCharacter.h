#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UThirdPersonCamera;
class AThirdPersonCamera;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class PROJECTECHIDNA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	void ProcessCharacterMovementInput(FVector2D input);
	void ProcessCameraMovementInput(FVector2D input) const;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float rotationSpeed = 10;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UThirdPersonCamera> cameraRef = nullptr;

private:
	FVector targetDirection;
	TObjectPtr<USkeletalMeshComponent> meshComponent;
};
