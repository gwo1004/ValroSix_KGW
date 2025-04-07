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
}

void UStatusWidget::SetPlayerShield(const int32& UpdateShield)
{
}

void UStatusWidget::SetPlayerAmmo(const int32& UpdateCurrentAmmo, const int32& UpdateRemainingAmmo)
{
}
