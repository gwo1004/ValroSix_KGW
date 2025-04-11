// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundStateWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class VALROSIX_KGW_API URoundStateWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetRoundStateTime(const int32& RoundTime);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;
	
};
