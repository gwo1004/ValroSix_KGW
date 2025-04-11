// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameMode/NormalGameMode.h"
#include "Core/GameMode/NormalGameState.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Core/Player/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

ANormalGameMode::ANormalGameMode()
{
	DefaultPawnClass = ABasePlayableCharacter::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	GameStateClass = ANormalGameState::StaticClass();
}

void ANormalGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartPreparationPhase();
}

void ANormalGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ANormalGameMode::StartPreparationPhase()
{
	if (ANormalGameState* GS = GetGameState<ANormalGameState>())
	{
		GS->RoundState = EGameRoundState::Preparation;
		GS->StartCountDown(15);
	}
}

void ANormalGameMode::StartRoundPhase()
{
	if (ANormalGameState* GS = GetGameState<ANormalGameState>())
	{
		GS->RoundState = EGameRoundState::RoundPlaying;
		GS->StartCountDown(90);
	}
}

void ANormalGameMode::OnCountDownFinished()
{
	if (ANormalGameState* GS = GetGameState<ANormalGameState>())
	{
		switch (GS->RoundState)
		{
		case EGameRoundState::Preparation:
			StartRoundPhase();
			break;
		case EGameRoundState::RoundPlaying:
			HandleRoundEnd(TEXT("Time Out"));
			break;
		case EGameRoundState::BomberPlant:
			HandleRoundEnd(TEXT("Bomber Can't Diffuse"));
			break;
		case EGameRoundState::RoundEnd:
			StartPreparationPhase();
			break;
		default:
			break;
		}
	}
}

void ANormalGameMode::HandleRoundEnd(FString Reason)
{
	if (ANormalGameState* GS = GetGameState<ANormalGameState>())
	{
		GS->RoundState = EGameRoundState::RoundEnd;
		GS->StartCountDown(10);
	}
}
