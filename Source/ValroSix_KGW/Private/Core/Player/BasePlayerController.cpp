// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Data/DataAssets/PlayerInputKeyData.h"
#include "UI/ViewModels/Player/InGamePlayerVM.h"
#include "UI/ViewModels/Shop/InGameShopVM.h"

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

// UI를 통한 조작키 변경 로직. NewIMC -> Player IMC에 반영하기
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

void ABasePlayerController::Client_ShowMainWidget_Implementation()
{
	if (IsLocalController() && InGameWidgetClass)
	{
		InGameWidget = CreateWidget<UInGamePlayerVM>(this, InGameWidgetClass);
		if (InGameWidget)
		{
			InGameWidget->SetOwningPlayer(this);
			InGameWidget->AddToViewport();
		}
	}
}

void ABasePlayerController::Client_ShowShopWidget_Implementation()
{
	if (IsLocalController() && ShopWidgetClass)
	{
		ShopWidget = CreateWidget<UInGameShopVM>(this, ShopWidgetClass);
		if(ShopWidget)
		{
			bShowMouseCursor = true;
			FInputModeGameAndUI CurrentUIMode;
			SetInputMode(CurrentUIMode);
			ShopWidget->SetOwningPlayer(this);
			ShopWidget->AddToViewport();
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABasePlayerController::Client_ShowMainWidget);
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABasePlayerController::Client_ShowShopWidget);
	}
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
