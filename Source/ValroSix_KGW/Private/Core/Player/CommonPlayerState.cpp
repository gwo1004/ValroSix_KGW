// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/CommonPlayerState.h"
#include "Characters/PlayerCharacter/BasePlayableCharacter.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "Kismet\GameplayStatics.h"

ACommonPlayerState::ACommonPlayerState()
{
	CurrentPlayerTeam = EGameTeam::TeamNotSelect;
}

void ACommonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACommonPlayerState, CurrentPlayerTeam);
}

void ACommonPlayerState::TeamChangedOutLine()
{
    APlayerController* LocalPC = GetWorld()->GetFirstPlayerController();
    if (!LocalPC) return;

    APawn* LocalPawn = LocalPC->GetPawn();
    if (!LocalPawn) return;

    ACommonPlayerState* LocalPS = Cast<ACommonPlayerState>(LocalPawn->GetPlayerState());
    if (!LocalPS) return;

    UE_LOG(LogTemp, Display, TEXT("Outline Call Test. - TeamChangedOutline Func"));

    for (ABasePlayableCharacter* OtherCharacter : TActorRange<ABasePlayableCharacter>(GetWorld()))
    {
        if (!OtherCharacter || OtherCharacter == LocalPawn) continue;

        ACommonPlayerState* OtherPS = Cast<ACommonPlayerState>(OtherCharacter->GetPlayerState());
        if (!OtherPS) continue;

        bool bSameTeam = (OtherPS->GetTeam() == LocalPS->GetTeam());
        int32 StencilValue = bSameTeam ? 1 : 2;

        USkeletalMeshComponent* Mesh = OtherCharacter->GetMesh();
        if (Mesh)
        {
            Mesh->SetRenderCustomDepth(true);
            Mesh->SetCustomDepthStencilValue(StencilValue);
            UE_LOG(LogTemp, Display, TEXT("Outline Call Test. - Mesh"));
        }
    }
}

void ACommonPlayerState::OnRep_Team()
{
	TeamChangedOutLine();
}

void ACommonPlayerState::SetTeam(EGameTeam Team)
{
	if (HasAuthority())
	{
		CurrentPlayerTeam = Team;
		OnRep_Team();

		APlayerController* PC = Cast<APlayerController>(GetOwner());
		if (!PC) return;
		UE_LOG(LogTemp, Log, TEXT("Current Player Owner : %s"), *PC->GetName());
		UE_LOG(LogTemp, Log, TEXT("CurrentPlayer Team to : %s"), *UEnum::GetValueAsString(CurrentPlayerTeam));
	}
}
