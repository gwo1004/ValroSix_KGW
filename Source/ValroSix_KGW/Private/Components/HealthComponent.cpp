// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Net\UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
//	SetUpHealthProperty();
}

void UHealthComponent::DamageHandle(float DamageAmount, AController* InstigateTarget, AActor* DamageCauser)
{
	if (bIsDead || DamageAmount <= 0.f) return;

	//if (GetOwner()->HasAuthority())
	//{
	//	//CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	//	CurrentHealth -= DamageAmount;
	//	UE_LOG(LogTemp, Display, TEXT("CurrentHP : %f"), CurrentHealth);

	//	if (CurrentHealth <= 0.f)
	//	{
	//		bIsDead = true;
	//	}
	//}

	if (GetOwner()->HasAuthority())
	{
		float Old = CurrentHealth;
		CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
		UE_LOG(LogTemp, Warning, TEXT("Server CurrentHealth changed: %f → %f"), Old, CurrentHealth);
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

	if (GetOwner()->HasAuthority())
	{
		SetUpHealthProperty();
	}
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
	UE_LOG(LogTemp, Display, TEXT("OnRepCallTest"));
	OnHealthChanged.Broadcast(CurrentHealth);

}
