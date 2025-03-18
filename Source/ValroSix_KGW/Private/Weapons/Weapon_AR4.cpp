// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon_AR4.h"
#include "Utility/LoggingCategories.h"

AWeapon_AR4::AWeapon_AR4()
{
	PrimaryActorTick.bCanEverTick = false;

	FireRate = 0.1f;
	bIsAuto = true;
}

void AWeapon_AR4::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_AR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
