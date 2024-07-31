#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonController.generated.h"


class AThirdPersonCamera;
class AMainCharacter;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;

UCLASS()
class PROJECTECHIDNA_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	void HandleMovement(const FInputActionValue& value);
	void HandleCameraMovement(const FInputActionValue& value);
	
private:
	void InitSystems();
	void SetupInputMappingContext();
	void SetupInputActions();

	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> thirdPersonContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput | Actions | Movement", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UInputAction> characterMovementAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput | Actions | Camera", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UInputAction> cameraMovementAction = nullptr;

	//refs
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AMainCharacter> characterRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputComponent> inputComponentRef = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> inputSubsystemRef = nullptr;
};
