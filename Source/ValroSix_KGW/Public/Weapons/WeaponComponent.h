// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
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

protected:
	virtual void BeginPlay() override;

public:
	// 무기 장착
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(TSubclassOf<class ABaseWeapon> WeaponClass);

	// 무기 장착 해제
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon();

	// 현재 장착된 무기
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	class ABaseWeapon* GetCurrentWeapon() const;

	// 발사
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireWeapon();
		
protected:
	// 현재 무기
	UPROPERTY()
	class ABaseWeapon* CurrentWeapon;

	// 부착할 캐릭터 소켓 이름
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachSocketName;
};
