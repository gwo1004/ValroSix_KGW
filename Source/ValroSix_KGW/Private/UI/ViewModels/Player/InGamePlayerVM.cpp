// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/Player/InGamePlayerVM.h"
#include "Utility/LoggingCategories.h"
#include "UI/Views/Player/StatusWidget.h"

void UInGamePlayerVM::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckNullObject(StatusWidget);
}

void UInGamePlayerVM::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGamePlayerVM::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInGamePlayerVM::CheckNullObject(UObject* CheckObject)
{
	if (!CheckObject)
	{
		UE_LOG(LogUI, Warning, TEXT("%s Class Is Null"), *CheckObject->GetName());
		return;
	}
}
