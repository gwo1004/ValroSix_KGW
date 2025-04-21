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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetCurrentShield(float UpdateShieldValue) { CurrentShield = UpdateShieldValue; }
	float GetCurrentShield() const { return CurrentShield; }
protected:
	virtual void BeginPlay() override;
	virtual void SetUpHealthProperty() override;

protected:
	UPROPERTY(EditDefaultsOnly, Replicated, Category ="Stat | Shield")
	float MaxShield;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentShield, VisibleAnywhere, Category = "Stat | Shield")
	float CurrentShield;

protected:
	UFUNCTION()
	void OnRep_CurrentShield();

public:
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FOnChangeCurrentValue OnShieldChanged;
};
