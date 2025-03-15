// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class VALROSIX_KGW_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:	

	bool CanEquip();
	void Equip();
	void BeginEquip();
	void EndEquip();

	bool CanUnEquip();
	void Unequip();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
	FName HolsterSocketName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FVector SocketOffset;
	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FRotator SocketRotationOffset;

private:
	class ABasePlayableCharacter* Owner;


};
