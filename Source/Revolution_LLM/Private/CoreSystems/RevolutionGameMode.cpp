// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/RevolutionGameMode.h"

void ARevolutionGameMode::BeginPlay()
{
	Super::BeginPlay();

	Suspect1GPT = NewObject<UGPTManager>(this, UGPTManager::StaticClass());

	if (Suspect1GPT)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,                   
				5.f,                 
				FColor::Red,          
				TEXT("Suspect1 init") 
			);
		}
	}

}