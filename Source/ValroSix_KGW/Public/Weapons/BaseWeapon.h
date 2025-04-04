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
	UFUNCTION(Server, Reliable)
	void Server_Fire();

	virtual void Fire();

	bool GetIsAuto() const { return bIsAuto; }
	float GetFireRate() const { return CurrentFireRate; }
	FVector GetSocketOffset() const { return SocketOffset; }
	FRotator GetSocketRotation() const { return SocketRotationOffset; }

protected:
	virtual void InitializedWeaponData();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	class UWeaponDataAsset* WeaponData;

	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FVector SocketOffset;
	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FRotator SocketRotationOffset;

protected:
	void HitDamage(const FHitResult& Hit);


// Replicate Properties
protected:
	UPROPERTY(VisibleAnywhere, Replicated)
	int32 CurrentAmmo;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 CurrentReserveAmmo;

	UPROPERTY(VisibleAnywhere, Replicated)
	float WeaponDefaultDamage;

	UPROPERTY(VisibleAnywhere, Replicated)
	float CurrentFireRate;

protected:
	UPROPERTY(EditAnywhere, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category = "Fire")
	bool bIsAuto = false;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRange = 1000.f;

protected:
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_DrawLine(FVector start, FVector end, bool bHit, FVector HitPoint);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_FireEffects();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FireSound();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SpawnImpactDecal(const FHitResult& Hit);
};
