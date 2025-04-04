// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/BasePlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UBasePlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.f;
	Direction = 0.f;
	bIsJump = false;
	bIsCrouch = false;
	AimPitch = 0.f;
	AimYaw = 0.f;
	BlendType = EWeaponType::Unarmed;
}

void UBasePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Owner = TryGetPawnOwner();

	if (!Owner) return;

	Speed = Owner->GetVelocity().Size();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

	ABasePlayableCharacter* Player = Cast<ABasePlayableCharacter>(Owner);
	if (!Player) return;

	bIsJump = Player->GetCharacterMovement()->IsFalling();
	bIsCrouch = Player->bIsCrouched;

	FRotator ControlRotation = Player->GetControlRotation();
	FRotator ActorRotation = Player->GetActorRotation();
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, ActorRotation);

	AimYaw = DeltaRot.Yaw;
	AimPitch = DeltaRot.Pitch;
}
