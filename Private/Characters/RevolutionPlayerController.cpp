// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/RevolutionPlayerController.h"
#include "InteractionActors/BaseCharacter.h"
#include "CoreSystems/RevolutionGameMode.h"
#include "InteractionActors/Mic.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractionActors/BaseInteractionActor.h"
#include "InteractionActors/BaseInteractionCharacter.h"

ARevolutionPlayerController::ARevolutionPlayerController()
{
	PrimaryActorTick.bCanEverTick = true; 
	CurrentFocusedActor = nullptr;

}

void ARevolutionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetManagerClass)
	{
		WidgetManager = NewObject<UWidgetManager>(this, WidgetManagerClass);
		WidgetManager->Initialize(this);
	}

	SetMouse(true);

	SetInputMode(FInputModeGameOnly());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UWorld* World = GetWorld())
	{
		AGameModeBase* GameMode = World->GetAuthGameMode();
		RevGameMode = Cast<ARevolutionGameMode>(GameMode);
	}

	SetGameUIMode(EGameUIMode::Lobby);
}



void ARevolutionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(ShootAction, ETriggerEvent::Started, this, &ARevolutionPlayerController::HandleInteraction);
	}
}

void ARevolutionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (UIMode == EGameUIMode::Normal)
	{
		TraceFromCrosshair();
	}
}

void ARevolutionPlayerController::TraceFromCrosshair()
{
	if (!PlayerCameraManager) return;

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);

	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.0f);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetPawn());

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			TraceStart,
			TraceEnd,
			ECC_Visibility,
			Params
		);

		bool bIsBaseInteractionActor = false;

		if (bHit && HitResult.GetActor())
		{
			if (ABaseInteractionActor* HitInteractionActor = Cast<ABaseInteractionActor>(HitResult.GetActor()))
			{
				bIsBaseInteractionActor = true;

				if (HitInteractionActor != CurrentFocusedActor)
				{
					if (CurrentFocusedActor)
					{
						CurrentFocusedActor->SetOutline(false);
					}
					CurrentFocusedActor = HitInteractionActor;
					CurrentFocusedActor->SetOutline(true);

					//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Tracked BaseInteractionActor"));
				}
			}
		}
		if (!bIsBaseInteractionActor && CurrentFocusedActor)
		{
			CurrentFocusedActor->SetOutline(false);
			CurrentFocusedActor = nullptr;
		}
	}
}

void ARevolutionPlayerController::HandleInteraction()
{
	if (UIMode != EGameUIMode::Normal) return;

	if (CurrentFocusedActor)
	{
		bool bHandledInternally = false;

		if (ABaseCharacter* BaseChar = Cast<ABaseCharacter>(CurrentFocusedActor))
		{
			UIMode = EGameUIMode::Talk;

			if (RevGameMode)
			{
				RevGameMode->SetSelectedSuspect(BaseChar->Number);
			}

			SetGameUIMode(EGameUIMode::Talk);
			bHandledInternally = true;
		}
		CurrentFocusedActor->OnInteract();
		CurrentFocusedActor->SetOutline(false);
		CurrentFocusedActor = nullptr;

		if (!bHandledInternally && UIMode == EGameUIMode::Normal)
		{

		}
	}
}

void ARevolutionPlayerController::SubmitResult(int32 value)
{
	Choice = value;
}

void ARevolutionPlayerController::SetGameUIMode(EGameUIMode NewMode)
{
	UIMode = NewMode;
	WidgetManager->HideAll();
	SetMouse(true);
	//SetInputMode(FInputModeUIOnly());
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	switch (NewMode)
	{
	case EGameUIMode::Lobby:
		WidgetManager->ShowUI("Lobby");
		break;
	case EGameUIMode::Normal:
		WidgetManager->ShowUI("HUD");
		SetMouse(false);
		SetInputMode(FInputModeGameOnly());
		break;
	case EGameUIMode::Talk:
		WidgetManager->ShowUI("Input");
		WidgetManager->ShowUI("Output");
		// load from TMap and cast to OutputWidget
		if (UUserWidget** FoundWidget = WidgetManager->WidgetMap.Find("Output"))
		{
			if (UOutputWidget* Output = Cast<UOutputWidget>(*FoundWidget))
			{
				if (RevGameMode)
				{
					if (RevGameMode->SelectedNumber == 1)
						Output->SetNameText(TEXT("Kang Minseok"));
					else if (RevGameMode->SelectedNumber == 2)
						Output->SetNameText(TEXT("Professor Sangjin Kim"));
					else if (RevGameMode->SelectedNumber == 3)
						Output->SetNameText(TEXT("Ji-eun Yoon"));
				}
			}
		}
		WidgetManager->ShowUI("Exit");
		break;
	case EGameUIMode::Computer:
		WidgetManager->ShowUI("Computer");
		WidgetManager->ShowUI("Exit");
		break;
	case EGameUIMode::CaseEnd:
		WidgetManager->ShowUI("CaseEnd");
		WidgetManager->ShowUI("Exit");
		break;
	case EGameUIMode::End:
		WidgetManager->ShowUI("Ending");
		// load from TMap and cast to OutputWidget
		if (UUserWidget** FoundWidget = WidgetManager->WidgetMap.Find("Ending"))
		{
			if (UOutputWidget* Ending = Cast<UOutputWidget>(*FoundWidget))
			{
				if (Choice == 1)
				{
					Ending->SetNameText(TEXT("Kang Minseok was killer! You Win!!!"));
				}
				else if (Choice == 2)
				{
					Ending->SetNameText(TEXT("Professor Sangjin Kim was innocent. You Lose."));
				}
				else if (Choice == 3)
				{
					Ending->SetNameText(TEXT("Ji-eun Yoon was innocent. You Lose."));
				}
			}
		}
		break;
	}
}


void ARevolutionPlayerController::SetMouse(bool bEnable)
{
	bShowMouseCursor = bEnable;
	bEnableClickEvents = bEnable;
	bEnableMouseOverEvents = bEnable;
}