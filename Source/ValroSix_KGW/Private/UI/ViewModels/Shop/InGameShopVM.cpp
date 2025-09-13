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
	PoplulateItemWidget();
}

void UInGameShopVM::NativeConstruct()
{
	Super::NativeConstruct();


}

void UInGameShopVM::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UInGameShopVM::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey PressKey = InKeyEvent.GetKey();

	if (PressKey == EKeys::B || PressKey == EKeys::Escape)
	{
		//CloseWidget();
		return FReply::Handled();
	}


	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

bool UInGameShopVM::CheckNullObject(UObject* CheckObject)
{
	if (!CheckObject)
	{
		UE_LOG(LogUI, Warning, TEXT("%s Class Is Null"), *CheckObject->GetName());
		return false;
	}
	return true;
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
	if(!CheckNullObject(UIInfoDataAsset)) return;

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

void UInGameShopVM::CloseWidget()
{
	SetIsFocusable(false);
	RemoveFromParent();

	if(APlayerController* PC = GetOwningPlayer())
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
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
