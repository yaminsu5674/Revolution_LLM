// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/CaseEnd.h"
#include "Characters/RevolutionPlayerController.h"

void ACaseEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACaseEnd::OnInteract()
{

	// camera move and show the senario
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		ARevolutionPlayerController* RevPC = Cast<ARevolutionPlayerController>(PC);
		if (RevPC)
		{
			RevPC->SetGameUIMode(EGameUIMode::CaseEnd);  // 예: 컴퓨터 모드로 전환
		}
	}


}