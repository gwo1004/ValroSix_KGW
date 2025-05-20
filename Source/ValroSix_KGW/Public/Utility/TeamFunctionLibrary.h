// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TeamFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VALROSIX_KGW_API UTeamFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Team")
	static bool IsActorSameTeam(AActor* Instigator, AActor* Target);
	
	UFUNCTION(BlueprintCallable, Category = "Team")
	static AController* GetActorController(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category= "Team")
	static APlayerState* GetActorPlayerState(const AActor* Actor);

};
