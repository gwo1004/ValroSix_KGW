// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameMode/NormalGameState.h"
#include "Core/GameMode/NormalGameMode.h"
#include "Net/UnrealNetwork.h"

ANormalGameState::ANormalGameState()
{
	CountdownTime = 0.f;
	CountdownStartTime = 0.f;
	DurationTime = 0.f;
	RoundState = EGameRoundState::Preparation;
	bReplicates = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = true;
}

void ANormalGameState::OnRep_RoundState()
{
	OnTimeChanged.Broadcast(CountdownTime);
}

void ANormalGameState::StartCountDown(float Duration)
{
	DurationTime = Duration;
	CountdownStartTime = GetWorld()->GetTimeSeconds();

	GetWorldTimerManager().SetTimer(CountDownTimer, this, &ANormalGameState::TickCountDown, 0.05f, true);
}

void ANormalGameState::TickCountDown()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	CountdownTime = FMath::Clamp(DurationTime - (CurrentTime - CountdownStartTime), 0.f, DurationTime);

	if (CountdownTime <= 0.f)
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
