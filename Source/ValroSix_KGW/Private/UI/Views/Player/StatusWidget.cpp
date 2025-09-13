// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Views/Player/StatusWidget.h"
#include "Components\TextBlock.h"

void UStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();

	CurrentHealth = nullptr;
	CurrentShield = nullptr;
	CurrentAmmo = nullptr;
	RemainingAmmo = nullptr;

}

void UStatusWidget::SetPlayerHealth(const int32& UpdateHealth)
{
	if (CurrentHealth)
	{
		CurrentHealth->SetText(FText::AsNumber(UpdateHealth));
	}
}

void UStatusWidget::SetPlayerShield(const int32& UpdateShield)
{
	if (CurrentShield)
	{
		CurrentShield->SetText(FText::AsNumber(UpdateShield));
	}
}

void UStatusWidget::SetWeaponCurrentAmmo(const int32& UpdateCurrentAmmo)
{
	if (CurrentAmmo)
	{
		CurrentAmmo->SetText(FText::AsNumber(UpdateCurrentAmmo));
	}
}

void UStatusWidget::SetWeaponReserveAmmo(const int32& UpdateReserveAmmo)
{
	if (RemainingAmmo)
	{
		RemainingAmmo->SetText(FText::AsNumber(UpdateReserveAmmo));
	}
}
