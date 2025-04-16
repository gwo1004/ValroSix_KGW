// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseItemWidget.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class VALROSIX_KGW_API UBaseItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	virtual void HoverItem();

	UFUNCTION()
	virtual void EquipItem();

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemTexture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;
	
	// DA(UI Info)
	// 
	// UI 내 추가사항
	// 보조무기, 기관단총, 스킬, 방어 등 타입 SubClass 분리 Weapon / SubWeapon / Skill / Armor
	// 아이템 이름	 ItemName
	// 아이템 가격	
	// 아이템 이미지 ItemTexture
	// 버튼			 ItemButton
	// 
	// 오버랩 경우
	// 아이템 이름
	// 아이템 이미지
	// 아이템 설명
	// - 공격력,최대거리,관통력 등 / 피해량 감소, 흡수한 피해등 각각의 설명
	//
	// 플레이어 받아와 장착된 무기 표시

	// 함수로 관리해야 하는 정보
	// GetOwingPlayer를 통한 플레이어 컨트롤러 및 GetPawn을 통한 플레이어 정보
	// 버튼 : 오버랩, 클릭 다이나믹
	// 오버랩 : 버튼색상 변경 - WBP 디자이너 / 아이템 설명 관련 
	// 클릭 : 해당 플레이어 캐릭터에게 선택한 아이템 제공, 해당 아이템 버튼 색상 변경(플레이어가 가지고 있는 인벤토리 정보를 통해 변경)

	
};
