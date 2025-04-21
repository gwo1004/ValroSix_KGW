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
			InGameWidget->Priority = 5;
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
			ShopWidget->SetIsFocusable(true);
			ShopWidget->SetOwningPlayer(this);
			ShopWidget->AddToViewport();
			ShopWidget->Priority = 10;

			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(ShopWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);

			bShowMouseCursor = true;

			ShopWidget->SetKeyboardFocus();
		}
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABasePlayerController::Client_ShowMainWidget);
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

/*
Shop 관련 위젯 관리 방법 
RemoveFromParent VS SetVisibility

CreateWidget / RemoveFromParent
장점 : 
런타임 내 바인딩된 FKey를 통한 동적 생성/제거와 같은 제어의 경우 메모리를 최소한으로 사용할 수 있다.

단점 :
특정 키를 입력한 생성/제거시 매번 생성비용 및 위젯 상태 유지가 힘들다.


SetVisibility
장점 :
세션 진입 및 Controller의 OnPossess시점에서 미리 생성하는 경우
Visibility를 설정만을 변경하기때문에 빠른 응답속도 보장 및 중복생성에 대한 문제가 없다.

단점 :
Render Thread 시점에서는 문제가 없지만, Game Thread에서는 항상 상점관련 데이터들을 메모리에 관리중.
메모리를 상시적으로 할당하며, 관리하고 있다.

SetVisibility를 사용한 이유 :

1. 빠른 응답속도 보장
 - 상점 위젯의 경우 에디터레벨에서 DA에 저장한 클래스 데이터만을 생성한다.
 - 즉, 런타임 내 상점 관련 변화되는 데이터가 없음으로 미리 생성하여 Visibility를 사용한 빠른 응답 보장을 채택.

2. 플레이어가 적용되어있는 아이템들에 대한 정보들을 유지하기 위함
 - Player의 인벤토리 역할을 하는 데이터들을 ShopWidget이 관리하고 있으며, Create/Remove시에는
   항상 WeaponComponent 또는 InventoryComponent에서 관련 데이터를 받아와야한다.
   Call Stack까지 고려하면 SetVisibility를 통한 상시 관리가 더 효율적.

3. 멀티플레이에서의 영향
 - 해당 위젯은 RPC (Client).
 - 위젯 생성은 클라이언트에서 하며, 데이터 전송시 장착되는 아이템에 대한 RPC(Server)를 사용한 요청
 - 따라서 위젯 생성 및 관리는 서버에는 영향이 없음으로 클라이언트 메모리를 부담하게하는 SerVisibility 사용

*/