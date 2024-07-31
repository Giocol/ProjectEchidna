#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UThirdPersonCamera;
class AThirdPersonCamera;
class UCameraComponent;

UCLASS()
class PROJECTECHIDNA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	void ProcessCharacterMovementInput(FVector2D input);
	void ProcessCameraMovementInput(FVector2D input);


protected:
	virtual void Tick(float deltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UThirdPersonCamera> cameraRef = nullptr;
};
