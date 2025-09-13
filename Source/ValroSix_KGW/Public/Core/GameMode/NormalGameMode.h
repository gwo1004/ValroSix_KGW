// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NormalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API ANormalGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ANormalGameMode();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void StartPreparationPhase();

	UFUNCTION()
	void StartRoundPhase();

	UFUNCTION()
	void OnCountDownFinished();
	
	UFUNCTION()
	void HandleRoundEnd(FString Reason);
};
