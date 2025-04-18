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

	ABaseWeapon* DefaultWeapon = ItemInfo.ItemClass->GetDefaultObject<ABaseWeapon>();
	if (!DefaultWeapon) return;

	EWeaponType WeaponType = DefaultWeapon->GetWeaponType();

	if (ABasePlayableCharacter* LocalPlayer = Cast<ABasePlayableCharacter>(GetOwningPlayerPawn()))
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponType : %d"), (int32)WeaponType);
		//LocalPlayer->
	}
}

void UWeaponItemWidget::SetItemDataBindingWidget(const FUIItemInfo& Data)
{
	Super::SetItemDataBindingWidget(Data);
}
