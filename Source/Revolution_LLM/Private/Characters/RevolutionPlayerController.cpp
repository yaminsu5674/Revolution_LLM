// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RevolutionPlayerController.h"
#include "CoreSystems/RevolutionGameMode.h"
#include "Blueprint/UserWidget.h"


void ARevolutionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Cyan,
			TEXT("PlayerController init")
		);
	}

	bShowMouseCursor = false;

	/*AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	if (CurrentGameMode && CurrentGameMode->IsA(ARevolutionGameMode::StaticClass()))
	{
		bShowMouseCursor = true;
	}
	else
	{
		bShowMouseCursor = false;
	}*/

	if (IsLocalController())
	{
		HUD = CreateWidget(this, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
}
