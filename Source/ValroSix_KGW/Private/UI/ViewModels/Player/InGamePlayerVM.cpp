// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/Player/InGamePlayerVM.h"
#include "Utility/LoggingCategories.h"
#include "UI/Views/Player/StatusWidget.h"
#include "Core/Player/BasePlayerController.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Components/PlayerHealthComponent.h"

void UInGamePlayerVM::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UInGamePlayerVM::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNullObject(StatusWidget);

	DelegateBinding();
}

void UInGamePlayerVM::NativeDestruct()
{
	Super::NativeDestruct();

	if (ABasePlayableCharacter* CurrentPlayer = Cast<ABasePlayableCharacter>(GetOwningPlayerPawn()))
	{
		if (CurrentPlayer->GetHealthComponent()->OnHealthChanged.IsBound())
		{
			CurrentPlayer->GetHealthComponent()->OnHealthChanged.RemoveDynamic(this, &UInGamePlayerVM::OnPlayerHealthBinding);
		}
	}
}

void UInGamePlayerVM::CheckNullObject(UObject* CheckObject)
{
	if (!CheckObject)
	{
		UE_LOG(LogUI, Warning, TEXT("%s Class Is Null"), *CheckObject->GetName());
		return;
	}
}

void UInGamePlayerVM::DelegateBinding()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	if (ABasePlayableCharacter* CurrentPlayer = Cast<ABasePlayableCharacter>(PC->GetPawn()))
	{
		CurrentPlayer->GetHealthComponent()->OnHealthChanged.AddDynamic(this, &UInGamePlayerVM::OnPlayerHealthBinding);
		OnPlayerHealthBinding(100.f);
	}
}

void UInGamePlayerVM::OnPlayerHealthBinding(float CurrentHealth)
{
	if (!StatusWidget) return;

	UE_LOG(LogUI, Warning, TEXT("Health updated: %f"), CurrentHealth);

	StatusWidget->SetPlayerHealth((int32)CurrentHealth);
}
