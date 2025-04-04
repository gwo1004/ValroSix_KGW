// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALROSIX_KGW_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	virtual void DamageHandle(float DamageAmount, AController* InstigateTarget,AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;
	virtual void SetUpHealthProperty();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat | Health")
	bool bIsDead;


};
