// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/Shop/InGameShopVM.h"
#include "Data/DataAssets/BaseItemDataAsset.h"
#include "UI/Views/Shop/WeaponItemWidget.h"
#include "Utility/LoggingCategories.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"

void UInGameShopVM::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindCategoryBox();
}

void UInGameShopVM::NativeConstruct()
{
	Super::NativeConstruct();
	PoplulateItemWidget();
}

void UInGameShopVM::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGameShopVM::CheckNullObject(UObject* CheckObject)
{
	if (!CheckObject)
	{
		UE_LOG(LogUI, Warning, TEXT("%s Class Is Null"), *CheckObject->GetName());
		return;
	}
}

TSubclassOf<class UBaseItemWidget> UInGameShopVM::GetWidgetClassByEnumWidgetType(EItemWidgetType Type)
{
	switch (Type)
	{
	case EItemWidgetType::Weapon:
		return WeaponWidgetClass;
	case EItemWidgetType::Armor:
		return ArmorWidgetClass;
	case EItemWidgetType::Ability:
		return AbilityWidgetClass;
	default:
		return nullptr;
	}
}

void UInGameShopVM::PoplulateItemWidget()
{
	CheckNullObject(UIInfoDataAsset);

	for (const FUIItemInfo& Info : UIInfoDataAsset->UIInfo)
	{
		TSubclassOf<UBaseItemWidget> WidgetClass = GetWidgetClassByEnumWidgetType(Info.WidgetType);
		if (!WidgetClass)
		{
			UE_LOG(LogUI, Error, TEXT("WidgetClass is Nullptr - UInGameShopVM.cpp"));
			continue;
		}
	
		UBaseItemWidget* ItemWidget = CreateWidget<UBaseItemWidget>(this, WidgetClass);
		if (!ItemWidget)
		{
			UE_LOG(LogUI, Error, TEXT("ItemWidget Create Fail"));
			continue;
		}

		if (UPanelWidget** TargetPanel = CategoryBoxMap.Find(Info.ItemCategory))
		{
			ItemWidget->SetItemDataBindingWidget(Info);
			(*TargetPanel)->AddChild(ItemWidget);
		}
	}

}

void UInGameShopVM::BindCategoryBox()
{
	CategoryBoxMap.Add(EItemCategory::SMG, SMGBox);
	CategoryBoxMap.Add(EItemCategory::Rifle, RifleBox);
	CategoryBoxMap.Add(EItemCategory::Sniper, SniperBox);
	CategoryBoxMap.Add(EItemCategory::Shotgun, ShotgunBox);
	CategoryBoxMap.Add(EItemCategory::MachineGun, MachineGunBox);
	CategoryBoxMap.Add(EItemCategory::SubPistol, SubPistolBox);
	CategoryBoxMap.Add(EItemCategory::Armor, ArmorBox);
	CategoryBoxMap.Add(EItemCategory::Ability, AbilityBox);
}
