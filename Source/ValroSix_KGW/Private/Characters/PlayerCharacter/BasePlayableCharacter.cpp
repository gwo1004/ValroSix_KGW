// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>
#include "Core/Player/BasePlayerController.h"
#include "Utility/LoggingCategories.h"
#include "Weapons/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/Animations/BasePlayerAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components\PlayerHealthComponent.h"

ABasePlayableCharacter::ABasePlayableCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	SpawnSetUpCamera();
	SpawnSetUpCharacterComponent();
	SpawnActorComponent();

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ABasePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!WeaponComponent)
	{
		UE_LOG(LogPlayer, Error, TEXT("WeaponComponent is Null"));
	}

	if (HasAuthority())
	{
		AttachWeapon();
	}
}

void ABasePlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
		{
			if (UPlayerInputKeyData* InputActions = Cast<UPlayerInputKeyData>(PC->ControlModeMap[EControlMode::Character].DataAsset))
			{
				BindMapToDataAsset();
				PC->SwitchControlMode(EControlMode::Character);
				//PC->UpdateCurrentIMC(PC->ControlModeMap[EControlMode::Character].DataAsset);
				
				for (const FPlayerInputKeyMapping& Mapping : InputActions->KeyMappings)
				{
					if (Mapping.InputAction && Mapping.Trigger != ETriggerEvent::None)
					{
						InputActionMap.Add(Mapping.InputActionEnum, Mapping.InputAction);
					}
				}

				for (const auto& Pair : InputActionBindings)
				{
					if (InputActionMap.Contains(Pair.Key))
					{
						UInputAction* IA = InputActionMap[Pair.Key];
						if (IA)
						{
							for (const FInputBindingInfo& BindingInfo : Pair.Value)
							{
								EnhancedInput->BindAction(IA, BindingInfo.Trigger, this, FName(BindingInfo.FunctionName));
							}
						}
					}
				}
			}
		}
	}
}

float ABasePlayableCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!HealthComponent)
	{
		UE_LOG(LogPlayer, Error, TEXT("HealthComponente is Null - BasePlayableCharacter.cpp"));
		return 0;
	}
	HealthComponent->DamageHandle(DamageAmount, EventInstigator, DamageCauser);

	return Damage;
}

void ABasePlayableCharacter::MoveForward(const FInputActionValue& Value)
{
	float MoveInput = Value.Get<float>();
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, MoveInput);
}

void ABasePlayableCharacter::MoveBack(const FInputActionValue& Value)
{
	float MoveInput = Value.Get<float>();
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, MoveInput);
}

void ABasePlayableCharacter::MoveRight(const FInputActionValue& Value)
{
	float MoveInput = Value.Get<float>();
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, MoveInput);
}

void ABasePlayableCharacter::MoveLeft(const FInputActionValue& Value)
{
	float MoveInput = Value.Get<float>();
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, MoveInput);
}

void ABasePlayableCharacter::Fire(const FInputActionValue& Value)
{
	UE_LOG(LogPlayer, Display, TEXT("Fire Func Call"));
	if (WeaponComponent)
	{
		WeaponComponent->FireWeapon();
	}
}

void ABasePlayableCharacter::EndFire(const FInputActionValue& Value)
{
	UE_LOG(LogPlayer, Display, TEXT("EndFire Func Call"));
	if (WeaponComponent)
	{
		WeaponComponent->EndFireWeapon();
	}
}

void ABasePlayableCharacter::LookUp(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ABasePlayableCharacter::InputJump(const FInputActionValue& Value)
{
	Super::Jump();
}

void ABasePlayableCharacter::InputCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Super::Crouch();
		UE_LOG(LogPlayer, Display, TEXT("InputCrount Func Call"));
	}
}

void ABasePlayableCharacter::StopCrouch(const FInputActionValue& Value)
{
	Super::UnCrouch();
	UE_LOG(LogPlayer, Display, TEXT("StopCrouch Func Call"));
}

void ABasePlayableCharacter::ConvertCameraActive(const FInputActionValue& Value)
{
	UE_LOG(LogPlayer, Display, TEXT("ConvertCameraActive Func Call"));
	bIsFPSCamera = !bIsFPSCamera;
	VisibilityMesh(bIsFPSCamera);
}

void ABasePlayableCharacter::SwitchPrimaryWeapon(const FInputActionValue& Value)
{
	SwitchCurrentWeapon((int32)EWeaponType::Rifle);
}

void ABasePlayableCharacter::SwitchPistolWeapon(const FInputActionValue& Value)
{
	SwitchCurrentWeapon((int32)EWeaponType::Pistol);
}

void ABasePlayableCharacter::SwitchMeleeWeapon(const FInputActionValue& Value)
{
	SwitchCurrentWeapon((int32)EWeaponType::Melee);
}


void ABasePlayableCharacter::VisibilityMesh(const bool& IsFPSCamera)
{
	if (GetMesh())
	{
		GetMesh()->SetOwnerNoSee(IsFPSCamera);
	}

	TPSCameraComp->SetActive(!IsFPSCamera);
	FPSCameraComp->SetActive(IsFPSCamera);
}

// TODO :Event 형식으로 UI와 연동, 해당 WeaponClass를 WeaponComponent에 추가 요청.
void ABasePlayableCharacter::AttachWeapon()
{
	if (WeaponComponent)
	{
		WeaponComponent->EquipWeapon(EWeaponType::Rifle, WeaponClass);
		WeaponComponent->EquipWeapon(EWeaponType::Pistol, SubWeaponClass);
		WeaponComponent->EquipWeapon(EWeaponType::Melee, MeleeWeaponClass);
	}
}

void ABasePlayableCharacter::SwitchCurrentWeapon(int32 WeaponType)
{
	UE_LOG(LogPlayer, Warning, TEXT("WeaponType Call : %d"), int32(WeaponType));

	if (WeaponComponent)
	{
		WeaponComponent->SwitchWeapon((EWeaponType)WeaponType);
		
		if (UBasePlayerAnimInstance* PlayerAnim = Cast<UBasePlayerAnimInstance>(GetMesh()->GetAnimInstance()))
		{
			PlayerAnim->SetWeaponType(WeaponComponent->GetCurrentWeaponType());
		}
	}
}

void ABasePlayableCharacter::SpawnSetUpCamera()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	FPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));

	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bUsePawnControlRotation = true;

	TPSCameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	TPSCameraComp->bUsePawnControlRotation = false;

	FPSCameraComp->SetupAttachment(RootComponent);
	FPSCameraComp->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	FPSCameraComp->bUsePawnControlRotation = true;

	bIsFPSCamera = false;

	TPSCameraComp->SetActive(!bIsFPSCamera);
	FPSCameraComp->SetActive(bIsFPSCamera);

}

void ABasePlayableCharacter::SpawnSetUpCharacterComponent()
{
	// Crouch
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(60.f);

	// AirControl
	GetCharacterMovement()->AirControl = 2.f;

	// Collisions
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ABasePlayableCharacter::SpawnActorComponent()
{
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	if (!WeaponComponent)
	{
		UE_LOG(LogPlayer, Error, TEXT("WeaponComponent CDO Fail"));
	}

	HealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>(TEXT("Health"));
	if (!HealthComponent)
	{
		UE_LOG(LogPlayer, Error, TEXT("HealthComponent CDO Fail"));
	}
}

void ABasePlayableCharacter::BindMapToDataAsset()
{
	InputActionBindings.Add(EPlayableInputAction::MoveForward, { {ETriggerEvent::Triggered, "MoveForward"} });
	InputActionBindings.Add(EPlayableInputAction::MoveBack, { {ETriggerEvent::Triggered, "MoveBack"} });
	InputActionBindings.Add(EPlayableInputAction::MoveRight, { {ETriggerEvent::Triggered, "MoveRight"} });
	InputActionBindings.Add(EPlayableInputAction::MoveLeft, { {ETriggerEvent::Triggered, "MoveLeft"} });
	InputActionBindings.Add(EPlayableInputAction::Jump, { {ETriggerEvent::Started, "InputJump"} });
	InputActionBindings.Add(EPlayableInputAction::LookUp, { {ETriggerEvent::Triggered, "LookUp"} });
	InputActionBindings.Add(EPlayableInputAction::ConvertCamera, { {ETriggerEvent::Started, "ConvertCameraActive"} });
	InputActionBindings.Add(EPlayableInputAction::PrimaryWeapon, { {ETriggerEvent::Started, "SwitchPrimaryWeapon"} });
	InputActionBindings.Add(EPlayableInputAction::PistolWeapon, { {ETriggerEvent::Started, "SwitchPistolWeapon"} });
	InputActionBindings.Add(EPlayableInputAction::MeleeWeapon, { {ETriggerEvent::Started, "SwitchMeleeWeapon"} });

	InputActionBindings.Add(EPlayableInputAction::Fire, {
		{ETriggerEvent::Started, "Fire"},
		{ETriggerEvent::Completed, "EndFire"}
		});

	InputActionBindings.Add(EPlayableInputAction::Crouch, {
		{ETriggerEvent::Started, "InputCrouch"},
		{ETriggerEvent::Completed, "StopCrouch"}
		});


}
