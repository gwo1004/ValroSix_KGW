// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameMode/NormalGameMode.h"
#include "Core/GameMode/NormalGameState.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Core/Player/BasePlayerController.h"
#include "Core/Player/CommonPlayerState.h"
#include "Utility\LoggingCategories.h"
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

	//ACommonPlayerState* PS = NewPlayer->GetPlayerState<ACommonPlayerState>();

	//if (!PS)
	//{
	//	UE_LOG(LogGameMode, Error, TEXT("PostLogin - PlayerState is Not Valid."));
	//	return;
	//}

	//if (PS->CurrentPlayerTeam != EGameTeam::TeamNotSelect) return;

	//int32 NumAttacker = 0;
	//int32 NumDefencer = 0;

	//for (APlayerState* SessionPS : GameState->PlayerArray)
	//{
	//	ACommonPlayerState* CurrentPS = Cast<ACommonPlayerState>(SessionPS);
	//	if (CurrentPS)
	//	{
	//		if (CurrentPS->CurrentPlayerTeam == EGameTeam::TeamAttacker) ++NumAttacker;
	//		else if (CurrentPS->CurrentPlayerTeam == EGameTeam::TeamDefender) ++NumDefencer;
	//	}
	//}
	//
	//if (NumAttacker <= NumDefencer)
	//{
	//	PS->SetTeam(EGameTeam::TeamAttacker);
	//}
	//else
	//{
	//	PS->SetTeam(EGameTeam::TeamDefender);
	//}


	ANormalGameState* GS = Cast<ANormalGameState>(UGameplayStatics::GetGameState(this));

	if (GS)
	{
		ACommonPlayerState* PS = NewPlayer->GetPlayerState<ACommonPlayerState>();

		if (PS && PS->GetTeam() == EGameTeam::TeamNotSelect)
		{
			if (GS->AttackTeam.Num() <= GS->DefenceTeam.Num())
			{
				GS->AttackTeam.AddUnique(PS);
				PS->SetTeam(EGameTeam::TeamAttacker);
			}
			else
			{
				GS->DefenceTeam.AddUnique(PS);
				PS->SetTeam(EGameTeam::TeamDefender);
			}
		}
		else
		{
			UE_LOG(LogGameMode, Error, TEXT("PostLogin - PlayerState is Not Valid."));
			return;
		}
	}
	else
	{
		UE_LOG(LogGameMode, Error, TEXT("PostLogin - GameState is Not Valid."));
		return;
	}
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
