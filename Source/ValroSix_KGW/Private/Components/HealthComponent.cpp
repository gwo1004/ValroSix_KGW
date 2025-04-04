// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Net\UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetUpHealthProperty();
}

void UHealthComponent::DamageHandle(float DamageAmount, AController* InstigateTarget, AActor* DamageCauser)
{
	if (bIsDead || DamageAmount <= 0.f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	UE_LOG(LogTemp, Display, TEXT("CurrentHP : %f"), CurrentHealth);

	if (CurrentHealth <= 0.f)
	{
		bIsDead = true;
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::SetUpHealthProperty()
{
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	bIsDead = false;
}

void UHealthComponent::OnRep_CurrentHealth()
{
	//UI Broadcast
}
