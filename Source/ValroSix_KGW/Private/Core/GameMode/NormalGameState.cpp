// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameMode/NormalGameState.h"
#include "Core/GameMode/NormalGameMode.h"
#include "Net/UnrealNetwork.h"

ANormalGameState::ANormalGameState()
{
	CountdownTime = 0;
	RoundState = EGameRoundState::Preparation;
	bReplicates = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = true;

}

void ANormalGameState::OnRep_RoundState()
{
	OnTimeChanged.Broadcast(CountdownTime);
}

void ANormalGameState::StartCountDown(int32 Duration)
{
	UE_LOG(LogTemp, Error, TEXT("Duration Call Text : %d"), Duration);
	CountdownTime = Duration;
	GetWorldTimerManager().SetTimer(CountDownTimer, this, &ANormalGameState::TickCountDown, 1.0f, true);
}

void ANormalGameState::TickCountDown()
{
	UE_LOG(LogTemp, Error, TEXT("Tick CountDown Text : %d"), CountdownTime);
	CountdownTime--;
	if (CountdownTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimer);

		if (HasAuthority())
		{
			if (ANormalGameMode* GM = Cast<ANormalGameMode>(GetWorld()->GetAuthGameMode()))
			{
				GM->OnCountDownFinished();
			}

		}
	}
}

void ANormalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANormalGameState, RoundState);
	DOREPLIFETIME(ANormalGameState, CountdownTime);
}
