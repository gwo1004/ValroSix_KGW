// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Views/Shop/WeaponItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"

void UWeaponItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWeaponItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWeaponItemWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWeaponItemWidget::HoverItem()
{
}

void UWeaponItemWidget::EquipItem()
{
	if (!ItemInfo.ItemClass) return;

	if (ABaseWeapon* DefaultWeapon = ItemInfo.ItemClass->GetDefaultObject<ABaseWeapon>())
	{
		if (ABasePlayableCharacter* LocalPlayer = Cast<ABasePlayableCharacter>(GetOwningPlayerPawn()))
		{
			LocalPlayer->Server_EquipWeapon((int32)DefaultWeapon->GetWeaponType(), ItemInfo.ItemClass);
		}
	}
}

void UWeaponItemWidget::SetItemDataBindingWidget(const FUIItemInfo& Data)
{
	Super::SetItemDataBindingWidget(Data);
}
