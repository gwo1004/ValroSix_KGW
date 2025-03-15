// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include <Components/SkeletalMeshComponent.h>

ABaseWeapon::ABaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Root;
	Mesh->SetupAttachment(RootComponent);
	HolsterSocketName = "WeaponSocket";
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ABasePlayableCharacter>(GetOwner());
	if (Owner && Owner->GetMesh() && HolsterSocketName.IsValid())
	{
		AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSocketName);
	}

	// SkeletalMesh 에 특정 소켓으로 부착
	// KeepRelative : 상대적인 위치를 유지하며 부착
	// true : 부착이 실패해도 실행을 계속
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseWeapon::CanEquip()
{
	return true;
}

void ABaseWeapon::Equip()
{
}

void ABaseWeapon::BeginEquip()
{
}

void ABaseWeapon::EndEquip()
{
}

bool ABaseWeapon::CanUnEquip()
{
	return true;
}

void ABaseWeapon::Unequip()
{
}

