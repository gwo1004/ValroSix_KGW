// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Data/DataAssets/PlayerInputKeyData.h"

ABasePlayerController::ABasePlayerController()
{
	CurrentMode = EControlMode::NONE;

	ControlModeMap.Add(EControlMode::Character, FControlModeMapping());
	ControlModeMap.Add(EControlMode::SkillPawn, FControlModeMapping());
}

void ABasePlayerController::SwitchControlMode(EControlMode Mode)
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (FControlModeMapping* ModeData = ControlModeMap.Find(Mode))
			{
				SubSystem->ClearAllMappings();
				SubSystem->AddMappingContext(ModeData->IMC, 0);
				CurrentMode = Mode;
			}
		}
	}
}

void ABasePlayerController::UpdateCurrentIMC(UPlayerInputKeyData* CurrentDataAsset)
{
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
