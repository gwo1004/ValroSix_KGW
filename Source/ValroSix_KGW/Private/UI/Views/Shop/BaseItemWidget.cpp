// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Views/Shop/BaseItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UBaseItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ItemButton && !ItemButton->OnHovered.IsBound())
	{
		ItemButton->OnHovered.AddDynamic(this, &UBaseItemWidget::HoverItem);
	}

	if (ItemButton && !ItemButton->OnClicked.IsBound())
	{
		ItemButton->OnClicked.AddDynamic(this, &UBaseItemWidget::EquipItem);
	}
}

void UBaseItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseItemWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseItemWidget::HoverItem()
{
}

void UBaseItemWidget::EquipItem()
{
}