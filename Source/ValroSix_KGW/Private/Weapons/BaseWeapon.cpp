// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include <Components/SkeletalMeshComponent.h>
#include "Utility/LoggingCategories.h"
#include "Kismet\GameplayStatics.h"

ABaseWeapon::ABaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(RootComponent);
	RootComponent = Mesh;

	bReplicates = true;
	SetReplicatingMovement(true);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
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
	FVector FireStart = TargetOwner->GetPawnViewLocation();
	FVector FireDirection = TargetOwner->GetControlRotation().Vector();

	FVector FireEnd = FireStart + (FireDirection * FireRange);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(TargetOwner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, FireStart, FireEnd, ECC_Visibility, QueryParams
	);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UE_LOG(LogWeapon, Warning, TEXT("Hit: %s"), *HitActor->GetName());
		}

		Multicast_DrawLine(FireStart, HitResult.ImpactPoint, true, HitResult.ImpactPoint);
	}
	else
	{
		Multicast_DrawLine(FireStart, FireEnd, false, FVector::ZeroVector);
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
