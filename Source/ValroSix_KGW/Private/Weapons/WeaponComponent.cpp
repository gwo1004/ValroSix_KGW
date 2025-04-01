// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "GameFramework\Character.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Utility\LoggingCategories.h"
#include "Net\UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentWeaponType = EWeaponType::Unarmed;
	CurrentWeapon = nullptr;
	bCanFire = true;
	WeaponAttachSocketName = TEXT("WeaponSocket");
	SetIsReplicatedByDefault(true);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponComponent::EquipWeapon(EWeaponType Slot, TSubclassOf<class ABaseWeapon> WeaponClass)
{
	ACharacter* TargetOwner = Cast<ACharacter>(GetOwner());

	if (!TargetOwner || !WeaponClass)
	{
		UE_LOG(LogWeapon, Error, TEXT("WeaponComponent_EquipWeapon Func Owner || WeaponClass nullptr"));
		return;
	}

	if (EquipWeapons.Contains(Slot) && EquipWeapons[Slot])
	{
		EquipWeapons[Slot]->Destroy();
		EquipWeapons[Slot] = nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = TargetOwner;
	SpawnParams.Instigator = TargetOwner->GetInstigator();
	ABaseWeapon* NewWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, SpawnParams);

	if (NewWeapon)
	{
		NewWeapon->AttachToComponent(TargetOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			WeaponAttachSocketName);
		NewWeapon->SetActorRelativeLocation(NewWeapon->GetSocketOffset());
		NewWeapon->SetActorRelativeRotation(NewWeapon->GetSocketRotation());
		NewWeapon->SetActorEnableCollision(false);

		EquipWeapons.Add(Slot, NewWeapon);
		SwitchWeapon(Slot);
	}
	// SkeletalMesh 에 특정 소켓으로 부착
	// KeepRelative : 상대적인 위치를 유지하며 부착
	// true : 부착이 실패해도 실행을 계속
}

void UWeaponComponent::SwitchWeapon(EWeaponType Slot)
{
	if (GetOwner()->HasAuthority())
	{
		Server_SwitchWeapon(Slot);
	}
	else
	{
		Server_SwitchWeapon(Slot);
	}
}

void UWeaponComponent::Server_SwitchWeapon_Implementation(EWeaponType Slot)
{
	ACharacter* TargetOwner = Cast<ACharacter>(GetOwner());

	if (!TargetOwner || !EquipWeapons.Contains(Slot))
	{
		UE_LOG(LogWeapon, Error, TEXT("WeaponComponent_SwitchWeapon Func Owner || Target Weapon Slot is nullptr"));
		return;
	}

	if (CurrentWeapon)
	{
		UnEquipWeapon();
	}

	CurrentWeapon = EquipWeapons[Slot];
	if (CurrentWeapon)
	{
		CurrentWeaponType = Slot;
		CurrentWeapon->SetActorHiddenInGame(false);
	}
}

void UWeaponComponent::UnEquipWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetActorHiddenInGame(true);
	}
}

void UWeaponComponent::FireWeapon()
{
	if (!CurrentWeapon)
	{
		UE_LOG(LogWeapon, Error, TEXT("Current Weapon is Not Valid. - WeaponComponent.cpp"));
		return;
	}
	if (!bCanFire) return;
	
	if (GetOwner()->HasAuthority())
	{
		CurrentWeapon->Fire();
	}
	else
	{
		CurrentWeapon->Server_Fire();
	}
	bCanFire = false;
	
	// TODO : Anim Notify를 사용한 애니메이션과 동기화.
	// 현재 로직은 발사중에 총기 변환시 Auto가 False인 총기에도 발사가 되고있음.
	// 해당 문제를 Notify를 사용한 리팩토링 예정.
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ResetFireTimer, this, &UWeaponComponent::ResetFire, CurrentWeapon->GetFireRate(), false);
	}

	if (CurrentWeapon->GetIsAuto() && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &UWeaponComponent::AutoFire, CurrentWeapon->GetFireRate(), true);
	}
}

void UWeaponComponent::EndFireWeapon()
{
	if (GetWorld() && AutoFireTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	}
}

void UWeaponComponent::OnRep_CurrentWeapon()
{
	if (!CurrentWeapon) return;

	//ACharacter* TargetOwner = Cast<ACharacter>(GetOwner());
	//if (!TargetOwner || !TargetOwner->GetMesh()) return;

	//CurrentWeapon->AttachToComponent(TargetOwner->GetMesh(),
	//	FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	//	WeaponAttachSocketName);

	//CurrentWeapon->SetActorRelativeLocation(CurrentWeapon->GetSocketOffset());
	//CurrentWeapon->SetActorRelativeRotation(CurrentWeapon->GetSocketRotation());
	//CurrentWeapon->SetActorEnableCollision(false);

	//UE_LOG(LogTemp, Warning, TEXT("[Client] Replicated weapon attached: %s"), *CurrentWeapon->GetName());
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponComponent, CurrentWeapon);
}

void UWeaponComponent::ResetFire()
{
	bCanFire = true;

	if (GetWorld()->GetTimerManager().IsTimerActive(ResetFireTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(ResetFireTimer);
	}
}

void UWeaponComponent::AutoFire()
{
	if (CurrentWeapon)
	{
		if (GetOwner()->HasAuthority())
		{
			CurrentWeapon->Fire();
		}
		else
		{
			CurrentWeapon->Server_Fire();
		}
	}
}
