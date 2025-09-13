// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon_Revolver.h"
#include "Utility/LoggingCategories.h"

AWeapon_Revolver::AWeapon_Revolver()
{
	PrimaryActorTick.bCanEverTick = false;

	bIsAuto = false;

	WeaponType = EWeaponType::Pistol;
}

void AWeapon_Revolver::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_Revolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
