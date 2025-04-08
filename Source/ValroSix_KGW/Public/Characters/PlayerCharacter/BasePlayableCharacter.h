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
class UWeaponComponent;
class UPlayerHealthComponent;

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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,AController* EventInstigator, AActor* DamageCauser) override;

	UPlayerHealthComponent* GetHealthComponent() const { return HealthComponent; }
	UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

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
	void EndFire(const FInputActionValue& Value);

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

	UFUNCTION()
	void SwitchPrimaryWeapon(const FInputActionValue& Value);
	UFUNCTION()
	void SwitchPistolWeapon(const FInputActionValue& Value);
	UFUNCTION()
	void SwitchMeleeWeapon(const FInputActionValue& Value);

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

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UPlayerHealthComponent* HealthComponent;

	// Weapons 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ABaseWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ABaseWeapon> SubWeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ABaseWeapon> MeleeWeaponClass;

	void AttachWeapon();
	void SwitchCurrentWeapon(int32 WeaponType);
private:
	void SpawnSetUpCamera();
	void SpawnSetUpCharacterComponent();
	void SpawnActorComponent();

	//BindAction DataAsset
	TMap<EPlayableInputAction, UInputAction*> InputActionMap;
	TMap<EPlayableInputAction, TArray<FInputBindingInfo>> InputActionBindings;

	void BindMapToDataAsset();
};
