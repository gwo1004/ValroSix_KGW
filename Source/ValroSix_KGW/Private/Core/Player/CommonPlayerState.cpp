// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/CommonPlayerState.h"
#include "Net/UnrealNetwork.h"

ACommonPlayerState::ACommonPlayerState()
{
	CurrentPlayerTeam = EGameTeam::TeamNotSelect;
}

void ACommonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACommonPlayerState, CurrentPlayerTeam);
}

void ACommonPlayerState::OnRep_Team()
{
	UE_LOG(LogTemp, Log, TEXT("CurrentPlayer Team to : %s"), *UEnum::GetValueAsString(CurrentPlayerTeam));
}

void ACommonPlayerState::SetTeam(EGameTeam Team)
{
	if (HasAuthority())
	{
		CurrentPlayerTeam = Team;
	}
}
