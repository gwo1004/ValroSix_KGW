// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/BasePlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"

void UBasePlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.f;
	bIsJump = false;
	bIsCrouch = false;
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
}
