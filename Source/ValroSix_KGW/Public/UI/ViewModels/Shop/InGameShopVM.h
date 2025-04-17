// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/DataAssets/BaseItemDataAsset.h"
#include "InGameShopVM.generated.h"

/**
 * 
 */

class UVerticalBox;
class UHorizontalBox;

UCLASS()
class VALROSIX_KGW_API UInGameShopVM : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void CheckNullObject(UObject* CheckObject);
	TSubclassOf<class UBaseItemWidget> GetWidgetClassByEnumWidgetType(EItemWidgetType Type);
	void PoplulateItemWidget();

private:
	void BindCategoryBox();
protected:
	UPROPERTY(meta = (BindWidget)) UVerticalBox* SMGBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* RifleBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* SniperBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* ShotgunBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* MachineGunBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* SubPistolBox;
	UPROPERTY(meta = (BindWidget)) UVerticalBox* ArmorBox;
	UPROPERTY(meta = (BindWidget)) UHorizontalBox* AbilityBox;

	TMap<EItemCategory, UPanelWidget*> CategoryBoxMap;
protected:
	UPROPERTY(EditAnywhere, Category = "UI|Shop")
	UBaseItemDataAsset* UIInfoDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI | Shop")
	TSubclassOf<class UBaseItemWidget> WeaponWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI | Shop")
	TSubclassOf<class UBaseItemWidget> ArmorWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI | Shop")
	TSubclassOf<class UBaseItemWidget> AbilityWidgetClass;
};
