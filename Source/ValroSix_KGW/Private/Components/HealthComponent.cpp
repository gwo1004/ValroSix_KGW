// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::DamageHandle()
{
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}
