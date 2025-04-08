// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerHealthComponent.h"
#include "Net\UnrealNetwork.h"

UPlayerHealthComponent::UPlayerHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	CurrentShield = 100.f;
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
	UE_LOG(LogTemp, Display, TEXT("PlayerHealth Component Damage Handle Call : %f"),DamageAmount);

	Super::DamageHandle(DamageAmount,InstigateTarget,DamageCauser);
}

void UPlayerHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerHealthComponent, CurrentShield);
	DOREPLIFETIME(UPlayerHealthComponent, MaxShield);
}

void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerHealthComponent::SetUpHealthProperty()
{
	Super::SetUpHealthProperty();


}

void UPlayerHealthComponent::OnRep_CurrentShield()
{
	// Shield Broadcast
	UE_LOG(LogTemp, Display, TEXT("OnRep Current Shield Call Test"));
	OnShieldChanged.Broadcast(CurrentShield);
}
