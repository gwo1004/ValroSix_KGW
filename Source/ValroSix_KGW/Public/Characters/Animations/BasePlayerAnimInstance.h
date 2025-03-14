// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BasePlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API UBasePlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsJump;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsCrouch;
	
};
