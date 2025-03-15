// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "Weapon_AR4.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API AWeapon_AR4 : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	AWeapon_AR4();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
