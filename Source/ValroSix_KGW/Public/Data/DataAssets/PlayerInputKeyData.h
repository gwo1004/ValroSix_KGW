// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "PlayerInputKeyData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayableInputAction : uint8
{
	MoveForward		UMETA(DisplayName = "Move Forward"),
	MoveBack		UMETA(DisplayName = "Move Back"),
	MoveRight		UMETA(DisplayName = "Move Right"),
	MoveLeft		UMETA(DisplayName = "Move Left"),
	LookUp			UMETA(DisplayName = "LookUp"),
	Fire			UMETA(DisplayName = "Fire"),
	Jump			UMETA(DisplayName = "Jump"),
	Crouch			UMETA(DisplayName = "Crouch"),
	ConvertCamera	UMETA(DisplayName = "Convert Camera")
};

USTRUCT(BlueprintType)
struct FPlayerInputKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayableInputAction InputActionEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKey DefaultKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKey CurrentKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETriggerEvent Trigger;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	TArray<UInputModifier*> Modifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanModify;
};

USTRUCT()
struct FInputBindingInfo
{
	GENERATED_BODY()

	UPROPERTY()
	ETriggerEvent Trigger;

	UPROPERTY()
	FName FunctionName;

	FInputBindingInfo() {}
	FInputBindingInfo(ETriggerEvent Trigger, FName FunctionName)
		: Trigger(Trigger), FunctionName(FunctionName) {}
};

UCLASS(BlueprintType)
class VALROSIX_KGW_API UPlayerInputKeyData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<FPlayerInputKeyMapping> KeyMappings;
};
