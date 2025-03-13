// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter/BasePlayableCharacter.h"


// Sets default values
ABasePlayableCharacter::ABasePlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

