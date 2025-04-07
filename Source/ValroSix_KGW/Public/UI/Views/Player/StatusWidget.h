// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class VALROSIX_KGW_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHealth;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentShield;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentAmmo;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RemainingAmmo;
};
