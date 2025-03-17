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
	virtual void Fire();

	FVector GetSocketOffset() const { return SocketOffset; }
	FRotator GetSocketRotation() const { return SocketRotationOffset; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FVector SocketOffset;
	UPROPERTY(EditAnywhere, Category = "Socket Offset")
	FRotator SocketRotationOffset;
};
