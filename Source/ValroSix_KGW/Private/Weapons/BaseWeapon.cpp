// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include <Components/SkeletalMeshComponent.h>
#include "Utility/LoggingCategories.h"
#include "Data\DataAssets\WeaponDataAsset.h"
#include "Kismet\GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Net\UnrealNetwork.h"
#include "Materials\MaterialInterface.h"

ABaseWeapon::ABaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	MuzzleSocketName = TEXT("MuzzleSocket");

	bReplicates = true;
	SetReplicatingMovement(true);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	InitializedWeaponData();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::Server_Fire_Implementation()
{
	Fire();
}

void ABaseWeapon::Fire()
{
	ACharacter* TargetOwner = Cast<ACharacter>(GetOwner());
	if (!TargetOwner)
	{
		UE_LOG(LogWeapon, Error, TEXT("TargetOwner is null - ABaseWeapon.cpp"));
		return;
	}

	Multicast_FireSound();
	Multicast_FireEffects();

	FVector FireStart = TargetOwner->GetPawnViewLocation();
	FVector FireDirection = TargetOwner->GetControlRotation().Vector();

	FVector FireEnd = FireStart + (FireDirection * FireRange);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(TargetOwner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, FireStart, FireEnd, ECC_Visibility, QueryParams
	);

	--CurrentAmmo;
	UE_LOG(LogWeapon, Warning, TEXT("CurrentAmmo : %d"), CurrentAmmo);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UE_LOG(LogWeapon, Warning, TEXT("Hit: %s"), *HitActor->GetName());
			UE_LOG(LogWeapon, Warning, TEXT("Damage : %f"), CurrentDamage);
		}

		Multicast_DrawLine(FireStart, HitResult.ImpactPoint, true, HitResult.ImpactPoint);
		SpawnImpactDecal(HitResult);
	}
	else
	{
		Multicast_DrawLine(FireStart, FireEnd, false, FVector::ZeroVector);
	}
}

void ABaseWeapon::InitializedWeaponData()
{
	CurrentAmmo = 100;
	CurrentReserveAmmo = 100;
	CurrentDamage = 50;
	CurrentFireRate = 1.f;

	if (!WeaponData)
	{
		UE_LOG(LogWeapon, Error, TEXT("WeaponDataAsset Not Wrapping."));
		return;
	}

	CurrentAmmo = WeaponData->MagazineSize;
	CurrentReserveAmmo = WeaponData->MaxAmmo;
	CurrentDamage = WeaponData->Damage;
	CurrentFireRate = WeaponData->FireRate;
}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseWeapon, CurrentAmmo);
	DOREPLIFETIME(ABaseWeapon, CurrentReserveAmmo);
	DOREPLIFETIME(ABaseWeapon, CurrentDamage);
	DOREPLIFETIME(ABaseWeapon, CurrentFireRate);
}

void ABaseWeapon::SpawnImpactDecal(const FHitResult& Hit)
{
	if (!WeaponData && !WeaponData->DecalEffect)
	{
		UE_LOG(LogWeapon, Error, TEXT("Weapon Data || Decal Effect is null"));
		return;
	}

	FRotator DecalRotation = Hit.ImpactNormal.Rotation();
	DecalRotation.Pitch += 180.f;

	UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		WeaponData->DecalEffect,
		WeaponData->DecalSize,
		Hit.ImpactPoint,
		DecalRotation,
		WeaponData->DecalLifeTime
	);
}

void ABaseWeapon::Multicast_FireEffects_Implementation()
{
	if (WeaponData && WeaponData->MuzzleFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			WeaponData->MuzzleFX,
			Mesh,
			MuzzleSocketName, // 소켓 이름
			FVector::ZeroVector, 
			FRotator(0.f,0.f,-90.f),
			EAttachLocation::SnapToTargetIncludingScale,
			true
		);
	}
}

void ABaseWeapon::Multicast_FireSound_Implementation()
{
	if (WeaponData && WeaponData->FireSound)
	{
		UGameplayStatics::SpawnSoundAttached(
			WeaponData->FireSound,
			Mesh,
			MuzzleSocketName
		);
	}
}

void ABaseWeapon::Multicast_DrawLine_Implementation(FVector start, FVector end, bool bHit, FVector HitPoint)
{
	DrawDebugLine(GetWorld(), start, end, bHit ? FColor::Red : FColor::Blue, false, 1.5f, 0, 2.0f);
	if (bHit)
	{
		DrawDebugPoint(GetWorld(), HitPoint, 10.0f, FColor::Yellow, false, 1.5f);
	}
}
