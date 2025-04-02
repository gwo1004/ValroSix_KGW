// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 MagazineSize;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* FireSound;
	
};

/*
동적으로 변화하지 않을 값들 만을 설정
그 외 동적으로 변화하는 값(CurrentAmmo, CurrentReserveAmmo)의 경우에는 접근성을 고려하여 Weapon 클래스에서 관리
*/