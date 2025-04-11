// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NormalGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameRoundState : uint8
{
	Preparation		UMETA(DisplayName = "Round Preparation"),
	RoundPlaying	UMETA(DisplayName = "Round Play"),
	BomberPlant		UMETA(DisplayName = "Bomber Plant"),
	RoundEnd		UMETA(DisplayName = "Preparation Next Round")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedTime, int32, TimeValue);

UCLASS()
class VALROSIX_KGW_API ANormalGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ANormalGameState();

	UPROPERTY(Replicated, BlueprintReadOnly)
	EGameRoundState RoundState;

	UFUNCTION()
	void OnRep_RoundState();

	UPROPERTY(ReplicatedUsing = OnRep_RoundState, BlueprintReadOnly)
	int32 CountdownTime;

	FTimerHandle CountDownTimer;

	UFUNCTION(BlueprintCallable)
	void StartCountDown(int32 Duration);

	UFUNCTION()
	void TickCountDown();
	
	UPROPERTY(BlueprintAssignable, Category = "UI | Events")
	FOnChangedTime OnTimeChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
