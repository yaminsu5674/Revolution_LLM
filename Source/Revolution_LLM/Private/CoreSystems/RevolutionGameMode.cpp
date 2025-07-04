// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/RevolutionGameMode.h"
#include "CoreSystems/RevolutionGameInstance.h"
#include "Characters/RevolutionPlayerController.h"
#include "Kismet/GameplayStatics.h"

ARevolutionGameMode::ARevolutionGameMode()
{

	PlayerControllerClass = ARevolutionPlayerController::StaticClass(); 
}

void ARevolutionGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (URevolutionGameInstance* MyGI = Cast<URevolutionGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGI->SpawnSuspects();
	}

	Suspect1GPT = NewObject<UGPTManager>(this, UGPTManager::StaticClass());

	/*if (Suspect1GPT)
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
	}*/

}


void ARevolutionGameMode::SaveInputString(const FString& input)
{
	InputString = input;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Blue,
			InputString
		);
	}
}