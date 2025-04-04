// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerHealthComponent.h"

UPlayerHealthComponent::UPlayerHealthComponent()
{
}

void UPlayerHealthComponent::DamageHandle(float DamageAmount, AController* InstigateTarget, AActor* DamageCauser)
{
	if (bIsDead || DamageAmount <= 0.f) return;

	if (CurrentShield > 0.f)
	{
		const float AbsorbtionDamage = FMath::Min(CurrentShield, DamageAmount);
		CurrentShield -= AbsorbtionDamage;
		DamageAmount -= AbsorbtionDamage;
	}

	Super::DamageHandle(DamageAmount,InstigateTarget,DamageCauser);
}

void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerHealthComponent::SetUpHealthProperty()
{
	Super::SetUpHealthProperty();


}
