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

void URoundStateWidget::SetRoundStateTime(const float& RoundTime)
{
	if (!TimeText) return;

	if (RoundTime <= 10.f)
	{
		int32 Sec = FMath::FloorToInt(RoundTime);
		int32 MSec = FMath::RoundToInt((RoundTime - Sec) * 100.f);
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%d:%02d"), Sec, MSec)));
	}
	else
	{
		int TotalTime = FMath::FloorToInt(RoundTime);
		int32 RoundMinutes = TotalTime / 60;
		int32 RoundSeconds = TotalTime % 60;
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%d:%02d"), RoundMinutes, RoundSeconds)));
	}


	
	//if (TimeText)
	//{
	//	FString FormattedString = FString::Printf(TEXT("%d:%02d"), RoundMinutes, RoundSeconds);
	//	TimeText->SetText(FText::FromString(FormattedString));
	//}
}
