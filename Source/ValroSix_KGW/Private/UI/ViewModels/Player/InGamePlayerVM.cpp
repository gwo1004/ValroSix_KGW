// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/Player/InGamePlayerVM.h"
#include "Utility/LoggingCategories.h"
#include "UI/Views/Player/StatusWidget.h"
#include "Core/Player/BasePlayerController.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Components/PlayerHealthComponent.h"
#include "Weapons/WeaponComponent.h"

void UInGamePlayerVM::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UInGamePlayerVM::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNullObject(StatusWidget);

	DelegateBinding();
}

void UInGamePlayerVM::NativeDestruct()
{
	Super::NativeDestruct();

	if (ABasePlayableCharacter* CurrentPlayer = Cast<ABasePlayableCharacter>(GetOwningPlayerPawn()))
	{
		if (CurrentPlayer->GetHealthComponent()->OnHealthChanged.IsBound())
		{
			CurrentPlayer->GetHealthComponent()->OnHealthChanged.RemoveDynamic(this, &UInGamePlayerVM::OnPlayerHealthBinding);
		}
	}
}

void UInGamePlayerVM::CheckNullObject(UObject* CheckObject)
{
	if (!CheckObject)
	{
		UE_LOG(LogUI, Warning, TEXT("%s Class Is Null"), *CheckObject->GetName());
		return;
	}
}

void UInGamePlayerVM::DelegateBinding()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	if (ABasePlayableCharacter* CurrentPlayer = Cast<ABasePlayableCharacter>(PC->GetPawn()))
	{
		CurrentPlayer->GetHealthComponent()->OnHealthChanged.AddDynamic(this, &UInGamePlayerVM::OnPlayerHealthBinding);
		CurrentPlayer->GetHealthComponent()->OnShieldChanged.AddDynamic(this, &UInGamePlayerVM::OnPlayerShieldBinding);
		OnPlayerHealthBinding(CurrentPlayer->GetHealthComponent()->GetMaxHealth());
		OnPlayerShieldBinding(CurrentPlayer->GetHealthComponent()->GetCurrentShield());

		CurrentPlayer->GetWeaponComponent()->OnChangedCurrentWeapon.AddDynamic(this, &UInGamePlayerVM::OnWeaponChanged);
	}
}

void UInGamePlayerVM::OnPlayerHealthBinding(float CurrentHealth)
{
	if (!StatusWidget) return;

	StatusWidget->SetPlayerHealth((int32)CurrentHealth);
}

void UInGamePlayerVM::OnPlayerShieldBinding(float CurrentShield)
{
	if (!StatusWidget) return;

	StatusWidget->SetPlayerShield((int32)CurrentShield);
}

void UInGamePlayerVM::OnWeaponChanged(ABaseWeapon* PrevWeapon, ABaseWeapon* CurrentWeapon)
{
	if (PrevWeapon)
	{
		PrevWeapon->OnCurrentAmmoChanged.RemoveDynamic(this, &UInGamePlayerVM::OnWeaponCurrentAmmo);
		PrevWeapon->OnReserveAmmoChanged.RemoveDynamic(this, &UInGamePlayerVM::OnWeaponReserveAmmo);
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->OnCurrentAmmoChanged.AddDynamic(this, &UInGamePlayerVM::OnWeaponCurrentAmmo);
		CurrentWeapon->OnReserveAmmoChanged.AddDynamic(this, &UInGamePlayerVM::OnWeaponReserveAmmo);
		OnWeaponCurrentAmmo(CurrentWeapon->GetCurrentAmmo());
		OnWeaponReserveAmmo(CurrentWeapon->GetReserveAmmo());
	}
}

void UInGamePlayerVM::OnWeaponCurrentAmmo(int32 CurrentAmmo)
{
	if (!StatusWidget) return;

	StatusWidget->SetWeaponCurrentAmmo(CurrentAmmo);
}

void UInGamePlayerVM::OnWeaponReserveAmmo(int32 ReserveAmmo)
{
	if (!StatusWidget) return;

	StatusWidget->SetWeaponReserveAmmo(ReserveAmmo);
}
