// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/RevolutionPlayerController.h"
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
	IsBasicMode = 1;
	IsInputMode = 0;
	CurrentFocusedActor = nullptr;
}

void ARevolutionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;

	SetInputMode(FInputModeGameOnly());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (HUDClass)
	{
		HUD = CreateWidget(this, HUDClass);
		if (HUD) HUD->AddToViewport();
	}

	if (InputClass)
	{
		Input = CreateWidget(this, InputClass);
	}

	if (ExitClass)
	{
		Exit = CreateWidget(this, ExitClass);
	}
}

void ARevolutionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();



	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (1)
		{
			EnhancedInput->BindAction(ShootAction, ETriggerEvent::Started, this, &ARevolutionPlayerController::HandleInteraction);
		}
	}
}

void ARevolutionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsBasicMode)
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

					GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Tracked BaseInteractionActor"));
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
	if (!IsBasicMode) return;

	if (CurrentFocusedActor)
	{
		if (Cast<AMic>(CurrentFocusedActor))
		{
			IsInputMode = 1;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Focused Actor is Mic!"));
		}
		CurrentFocusedActor->OnInteract(); 

		SetBasicMode(0);
	}
}


void ARevolutionPlayerController::SetBasicMode(bool bEnable)
{
	IsBasicMode = bEnable ? 1 : 0;

	bShowMouseCursor = !bEnable;
	bEnableClickEvents = !bEnable;
	bEnableMouseOverEvents = !bEnable;

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Yellow,
		FString::Printf(TEXT("SetBasicMode called with bEnable = %s"), bEnable ? TEXT("true") : TEXT("false"))
	);


	// HUD 제거
	if (HUD)
	{
		HUD->RemoveFromParent();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("HUD removed."));
		HUD = nullptr;
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("HUD was already nullptr."));
	}

	// Exit 제거
	if (Exit)
	{
		Exit->RemoveFromParent();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Exit removed."));
		Exit = nullptr;
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Exit was already nullptr."));
	}

	// Input 제거
	if (Input)
	{
		Input->RemoveFromParent();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Input removed."));
		Exit = nullptr;
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Input was already nullptr."));
	}

	// 모드 전환 후 새 위젯 생성
	if (IsBasicMode)
	{
		IsInputMode = 0;
		SetInputMode(FInputModeGameOnly());

		if (HUDClass)
		{
			HUD = CreateWidget(this, HUDClass);
			if (HUD)
			{
				HUD->AddToViewport();
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("HUD created and added to viewport."));
			}
			else
			{
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("HUD widget creation failed!"));
			}
		}
	}
	else
	{
		if (ExitClass)
		{
			Exit = CreateWidget(this, ExitClass);
			if (Exit)
			{
				Exit->AddToViewport();
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Exit widget created and added to viewport."));
			}
			else
			{
				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Exit widget creation failed!"));
			}

			if (IsInputMode)
			{
				Input = CreateWidget(this, InputClass);
				if (Input)
				{
					Input->AddToViewport();
				}
			}
		}
	}
}