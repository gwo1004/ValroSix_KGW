// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	WeaponAttachSocketName = TEXT("WeaponSocket");
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::EquipWeapon(TSubclassOf<class ABaseWeapon> WeaponClass)
{
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (WeaponClass)
		{
			UnEquipWeapon();

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwnerCharacter;
			SpawnParams.Instigator = OwnerCharacter->GetInstigator();
		
			CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, SpawnParams);
			if (CurrentWeapon)
			{
				CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(),
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					WeaponAttachSocketName);
			}
		}
	}
}

void UWeaponComponent::UnEquipWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}
}

ABaseWeapon* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

void UWeaponComponent::FireWeapon()
{
	if (CurrentWeapon)
	{
		//CurrentWeapon->Fire();
	}
}
