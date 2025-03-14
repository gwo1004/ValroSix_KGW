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
	bool bHasPawn = (GetPawn() != nullptr);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (auto& ControlMap : ControlModeMap)
			{
				if (ControlMap.Value.DataAsset == CurrentDataAsset)
				{
					UInputMappingContext* NewIMC = NewObject<UInputMappingContext>(this);

					for (const FPlayerInputKeyMapping& Mapping : CurrentDataAsset->KeyMappings)
					{
						if (Mapping.InputAction && Mapping.CurrentKey.IsValid())
						{
							FEnhancedActionKeyMapping& NewMapping = NewIMC->MapKey(Mapping.InputAction, Mapping.CurrentKey);
							for (UInputModifier* Modifier : Mapping.Modifiers)
							{
								if (Modifier)
								{
									NewMapping.Modifiers.Add(Modifier);
								}
							}
						}
					}

					ControlMap.Value.IMC = NewIMC;
					if (bHasPawn && ControlMap.Key == CurrentMode)
					{
						SubSystem->ClearAllMappings();
						SubSystem->AddMappingContext(NewIMC, 0);
					}
				}
			}
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
