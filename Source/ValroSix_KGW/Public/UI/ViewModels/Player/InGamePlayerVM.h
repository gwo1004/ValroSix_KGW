// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGamePlayerVM.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API UInGamePlayerVM : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void CheckNullObject(UObject* CheckObject);
	void DelegateBinding();

	UFUNCTION()
	void OnPlayerHealthBinding(float CurrentHealth);

	UFUNCTION()
	void OnPlayerShieldBinding(float CurrentShield);

	UFUNCTION()
	void OnWeaponChanged(class ABaseWeapon* PrevWeapon, class ABaseWeapon* CurrentWeapon);

	UFUNCTION()
	void OnWeaponCurrentAmmo(int32 CurrentAmmo);

	UFUNCTION()
	void OnWeaponReserveAmmo(int32 ReserveAmmo);

protected:
	UPROPERTY(meta = (BindWidget))
	class UStatusWidget* StatusWidget;
	
	
};
