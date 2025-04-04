// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed UMETA(DisplayName = "UnArmed"),
	Rifle	UMETA(DisplayName = "Rifle"),
	Pistol	UMETA(DisplayName = "Pistol"),
	Melee	UMETA(DisplayName = "Melee")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InCurrentType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALROSIX_KGW_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

public:
	virtual void BeginPlay() override;

public:
	// 무기 장착
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(EWeaponType Slot, TSubclassOf<class ABaseWeapon> WeaponClass);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SwitchWeapon(EWeaponType Slot);

	UFUNCTION(Server, Reliable)
	void Server_SwitchWeapon(EWeaponType Slot);

	// 무기 장착 해제
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon();

	// 현재 장착된 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	class ABaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	// 발사
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EndFireWeapon();

	EWeaponType GetCurrentWeaponType() const { return CurrentWeaponType; }
	
	UFUNCTION()
	void OnRep_CurrentWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY()
	EWeaponType CurrentWeaponType;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon)
	class ABaseWeapon* CurrentWeapon;
	UPROPERTY()
	TMap<EWeaponType, ABaseWeapon*> EquipWeapons;

	// 부착할 캐릭터 소켓 이름
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachSocketName;

private:
	bool bCanFire;
	FTimerHandle ResetFireTimer;
	void ResetFire();

	FTimerHandle AutoFireTimer;
	void AutoFire();
};
