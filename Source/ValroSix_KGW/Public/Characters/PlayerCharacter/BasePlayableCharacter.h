// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/DataAssets/PlayerInputKeyData.h"
#include "BasePlayableCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputAction;
struct FInputActionValue;

UCLASS()
class VALROSIX_KGW_API ABasePlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABasePlayableCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//Enhanced Input Actions Function
	UFUNCTION()
	void MoveForward(const FInputActionValue& Value);

	UFUNCTION()
	void MoveBack(const FInputActionValue& Value);

	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);

	UFUNCTION()
	void MoveLeft(const FInputActionValue& Value);

	UFUNCTION()
	void Fire(const FInputActionValue& Value);

	UFUNCTION()
	void LookUp(const FInputActionValue& Value);

	UFUNCTION()
	void InputJump(const FInputActionValue& Value);

	UFUNCTION()
	void InputCrouch(const FInputActionValue& Value);

	UFUNCTION()
	void StopCrouch(const FInputActionValue& Value);

	UFUNCTION()
	void ConvertCameraActive(const FInputActionValue& Value);

protected:
	// Camera Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* TPSCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FPSCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera");
	bool bIsFPSCamera;

	// Convert Camera Mesh Settings
	void VisibilityMesh(const bool& IsFPSCamera);

private:
	void SpawnSetUpCamera();
	void SpawnSetUpCharacterComponent();

	//BindAction DataAsset
	TMap<EPlayableInputAction, UInputAction*> InputActionMap;
	TMap<EPlayableInputAction, TArray<FInputBindingInfo>> InputActionBindings;

	void BindMapToDataAsset();
};
