// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "Weapon_Knife.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API AWeapon_Knife : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	AWeapon_Knife();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
