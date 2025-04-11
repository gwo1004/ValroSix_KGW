// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Views/InGame/RoundStateWidget.h"
#include "Components/TextBlock.h"

void URoundStateWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URoundStateWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URoundStateWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void URoundStateWidget::SetRoundStateTime(const int32& RoundTime)
{
	if (TimeText)
	{
		TimeText->SetText(FText::AsNumber(RoundTime));
	}

}
