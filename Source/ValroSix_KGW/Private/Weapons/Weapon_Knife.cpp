// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon_Knife.h"
#include "Utility\LoggingCategories.h"

AWeapon_Knife::AWeapon_Knife()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponType = EWeaponType::Melee;
}

void AWeapon_Knife::Fire()
{
	UE_LOG(LogWeapon, Display, TEXT("Knife Call"));
}

void AWeapon_Knife::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_Knife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



