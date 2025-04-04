// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UPlayerInputKeyData;

UENUM(BlueprintType)
enum class EControlMode : uint8
{
	NONE	  UMETA(DisplayName = "None"),
	Character UMETA(DisplayName = "Character"),
	SkillPawn UMETA(DisplayName = "SkillPawn")
};

USTRUCT(BlueprintType)
struct FControlModeMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UPlayerInputKeyData* DataAsset;
};

UCLASS()
class VALROSIX_KGW_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABasePlayerController();
	
	UFUNCTION()
	void SwitchControlMode(EControlMode Mode);

	UFUNCTION()
	void UpdateCurrentIMC(UPlayerInputKeyData* CurrentDataAsset);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TMap<EControlMode, FControlModeMapping> ControlModeMap;
	
private:
	EControlMode CurrentMode;
};
