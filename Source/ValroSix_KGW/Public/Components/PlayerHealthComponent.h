// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "PlayerHealthComponent.generated.h"

UCLASS()
class VALROSIX_KGW_API UPlayerHealthComponent : public UHealthComponent
{
	GENERATED_BODY()
	
public:
	UPlayerHealthComponent();
	virtual void DamageHandle(float DamageAmount, AController* InstigateTarget, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetUpHealthProperty() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Stat | Shield")
	float MaxShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Shield")
	float CurrentShield;
};
