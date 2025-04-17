// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Views/Shop/BaseItemWidget.h"
#include "WeaponItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API UWeaponItemWidget : public UBaseItemWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	virtual void HoverItem() override;

	virtual void EquipItem() override;
	
public:
	virtual void SetItemDataBindingWidget(const FUIItemInfo& Data) override;
};
