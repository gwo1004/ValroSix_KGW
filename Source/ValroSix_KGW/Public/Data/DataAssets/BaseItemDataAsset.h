// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapons\BaseWeapon.h"
#include "BaseItemDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemWidgetType : uint8
{
	Weapon	UMETA(DisplayName = "무기"),
	Armor	UMETA(DisplayName = "방어구"),
	Ability	UMETA(DisplayName = "스킬")
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	SMG			UMETA(DisplayName = "기관단총"),
	Rifle		UMETA(DisplayName = "소총"),
	Sniper		UMETA(DisplayName = "저격소총"),
	Shotgun		UMETA(DisplayName = "산탄총"),
	MachineGun	UMETA(DisplayName = "기관총"),
	SubPistol	UMETA(DisplayName = "보조 무기"),
	Armor		UMETA(DisplayName = "방어"),
	Ability		UMETA(DisplayName = "스킬")
};

USTRUCT(BlueprintType)
struct FUIItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemWidgetType WidgetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemCategory ItemCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABaseWeapon> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ComponentValue;
};

UCLASS()
class VALROSIX_KGW_API UBaseItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TArray<FUIItemInfo> UIInfo;
	
};
