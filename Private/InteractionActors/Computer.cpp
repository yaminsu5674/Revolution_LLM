// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Computer.h"
#include "Characters/RevolutionPlayerController.h"

void AComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AComputer::OnInteract()
{

	// camera move and show the senario
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		ARevolutionPlayerController* RevPC = Cast<ARevolutionPlayerController>(PC);
		if (RevPC)
		{
			RevPC->SetGameUIMode(EGameUIMode::Computer);  // 예: 컴퓨터 모드로 전환
		}
	}

	
}