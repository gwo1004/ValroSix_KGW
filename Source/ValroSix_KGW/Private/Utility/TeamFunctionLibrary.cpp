// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TeamFunctionLibrary.h"
#include "Core/Player/CommonPlayerState.h"

bool UTeamFunctionLibrary::IsActorSameTeam(AActor* Instigator, AActor* Target)
{
	if (!Instigator || !Target) return false;

	// 설정한 함수로 PS 가져오기
	const APlayerState* InstigatorPS = GetActorPlayerState(Instigator);
	const APlayerState* TargetPS = GetActorPlayerState(Target);

	// 가져온 PS를 Team정보를 저장하는 PS클래스로 캐스팅
	const ACommonPlayerState* InstigatorTeamPS = Cast<const ACommonPlayerState>(InstigatorPS);
	const ACommonPlayerState* TargetTeamPS = Cast<const ACommonPlayerState>(TargetPS);

	// 둘다 nullptr이 아닌경우 확인(Team관련 정보를 가지고 올 수 있는 경우)
	if (!InstigatorTeamPS || !TargetTeamPS) return false;

	return InstigatorTeamPS->GetTeam() == TargetTeamPS->GetTeam();
}

AController* UTeamFunctionLibrary::GetActorController(const AActor* Actor)
{
	if (!Actor) return nullptr;

	// 먼저 Pawn 개체인지 확인
	if (const APawn* Pawn = Cast<APawn>(Actor))
	{
		return Pawn->GetController();
	}

	// Pawn이 아닐경우 GetOwner를 사용한 해당 Pawn 호출
	if(const APawn* ActorOwner = Cast<APawn>(Actor->GetOwner()))
	{
		return ActorOwner->GetController();	
	}

	// Trace와 같은 투사체일 경우
	if (const AController* ControllerInstigator = Actor->GetInstigatorController())
	{
		return const_cast<AController*>(ControllerInstigator);
	}

	return nullptr;
}

APlayerState* UTeamFunctionLibrary::GetActorPlayerState(const AActor* Actor)
{
	if (AController* Controller = GetActorController(Actor))
	{
		return Controller->PlayerState;
	}


	return nullptr;
}
