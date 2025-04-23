// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/BaseWeapon.h"
#include "WeaponComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, ABaseWeapon*, InPrevType, ABaseWeapon*, InCurrentType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALROSIX_KGW_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(EWeaponType Slot, TSubclassOf<class ABaseWeapon> WeaponClass);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SwitchWeapon(EWeaponType Slot);

	UFUNCTION(Server, Reliable)
	void Server_SwitchWeapon(EWeaponType Slot);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	class ABaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EndFireWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadAmmo();

	EWeaponType GetCurrentWeaponType() const { return CurrentWeaponType; }
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentWeapon();
protected:
	UPROPERTY()
	EWeaponType CurrentWeaponType;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon)
	ABaseWeapon* CurrentWeapon;
	UPROPERTY()
	ABaseWeapon* PrevWeapon;

	UPROPERTY()
	TMap<EWeaponType, ABaseWeapon*> EquipWeapons;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachSocketName;

public:
	UPROPERTY(BlueprintAssignable, Category = "UI | Ammo")
	FWeaponTypeChanged OnChangedCurrentWeapon;

private:
	bool bCanFire;
	FTimerHandle ResetFireTimer;
	void ResetFire();

	FTimerHandle AutoFireTimer;
	void AutoFire();
};
