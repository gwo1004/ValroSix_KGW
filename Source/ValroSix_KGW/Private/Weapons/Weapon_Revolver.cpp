// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon_Revolver.h"

AWeapon_Revolver::AWeapon_Revolver()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon_Revolver::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_Revolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
