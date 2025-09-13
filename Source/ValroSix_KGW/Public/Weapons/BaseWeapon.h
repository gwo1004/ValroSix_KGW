// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed UMETA(DisplayName = "UnArmed"),
	Rifle	UMETA(DisplayName = "Rifle"),
	Pistol	UMETA(DisplayName = "Pistol"),
	Melee	UMETA(DisplayName = "Melee")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedAmmo, int32, AmmoValue);

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

	UFUNCTION(Server, Reliable)
	void Server_Reload();

	virtual void Fire();
	virtual void Reload();
	virtual void ConsumeAmmo();

	bool GetIsAuto() const { return bIsAuto; }
	float GetFireRate() const { return CurrentFireRate; }
	FVector GetSocketOffset() const { return SocketOffset; }
	FRotator GetSocketRotation() const { return SocketRotationOffset; }
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
	int32 GetReserveAmmo() const { return CurrentReserveAmmo; }
	EWeaponType GetWeaponType() const { return WeaponType; }

protected:
	virtual void InitializedWeaponData();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void HitDamage(const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	class UWeaponDataAsset* WeaponData;

	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FVector SocketOffset;
	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FRotator SocketRotationOffset;

	UPROPERTY()
	EWeaponType WeaponType;
//	Delegates
public:
	UPROPERTY(BlueprintAssignable, Category = "UI | Ammo")
	FOnChangedAmmo OnCurrentAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI | Ammo")
	FOnChangedAmmo OnReserveAmmoChanged;

// Replicate Properties
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentAmmo)
	int32 CurrentAmmo;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentReserveAmmo)
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
	UFUNCTION()
	void OnRep_CurrentAmmo();

	UFUNCTION()
	void OnRep_CurrentReserveAmmo();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_DrawLine(FVector start, FVector end, bool bHit, FVector HitPoint);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_FireEffects();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FireSound();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SpawnImpactDecal(const FHitResult& Hit);
};
