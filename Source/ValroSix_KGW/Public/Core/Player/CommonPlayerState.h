// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CommonPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameTeam : uint8
{
	TeamAttacker	UMETA(DisplayName = "Attack Team"),
	TeamDefender	UMETA(DisplayName = "Defence Team"),
	TeamPersonal	UMETA(DisplayName = "Personal Team"),
	TeamNotSelect	UMETA(DisplayName = "Not Setting Team")
};

UCLASS()
class VALROSIX_KGW_API ACommonPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACommonPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	 
	UPROPERTY(ReplicatedUsing=OnRep_Team)
	EGameTeam CurrentPlayerTeam;

	UFUNCTION()
	void OnRep_Team();
	
	UFUNCTION()
	void SetTeam(EGameTeam Team);

};
