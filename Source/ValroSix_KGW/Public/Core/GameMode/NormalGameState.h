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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedTime, float, TimeValue);

UCLASS()
class VALROSIX_KGW_API ANormalGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ANormalGameState();

	UFUNCTION(BlueprintCallable)
	void StartCountDown(float Duration);

public:
	UPROPERTY(ReplicatedUsing = OnRep_RoundState)
	EGameRoundState RoundState;

	UPROPERTY(BlueprintAssignable, Category = "UI | Events")
	FOnChangedTime OnTimeChanged;

	TArray<class ACommonPlayerState*> AttackTeam;
	TArray<class ACommonPlayerState*> DefenceTeam;

protected:
	UFUNCTION()
	void OnRep_TimeState();

	UFUNCTION()
	void OnRep_RoundState();

	UPROPERTY(ReplicatedUsing = OnRep_TimeState, BlueprintReadOnly)
	float CountdownTime;
	float CountdownStartTime;
	float DurationTime;
	FTimerHandle CountDownTimer;

	UFUNCTION()
	void TickCountDown();
	


protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
