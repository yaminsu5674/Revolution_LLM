// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/RevolutionPlayerController.h"
#include "CoreSystems/RevolutionGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractionActors/BaseInteractionActor.h"

ARevolutionPlayerController::ARevolutionPlayerController()
{
	PrimaryActorTick.bCanEverTick = true; // Tick 활성화
	IsBasicMode = 1;
	CurrentFocusedActor = nullptr;
}

void ARevolutionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;

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
		if (Input) Input->AddToViewport();
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

//void ARevolutionPlayerController::TraceFromCrosshair()
//{
//	int32 ViewportSizeX, ViewportSizeY;
//	GetViewportSize(ViewportSizeX, ViewportSizeY);
//	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);
//
//	FHitResult HitResult;
//	if (GetHitResultAtScreenPosition(ScreenCenter, ECC_Visibility, true, HitResult))
//	{
//		if (AActor* HitActor = HitResult.GetActor())
//		{
//			ABaseInteractionActor* HitInteractionActor = Cast<ABaseInteractionActor>(HitActor);
//
//			// 라인트레이스로 새로운 액터 감지 시
//			if (HitInteractionActor && HitInteractionActor != CurrentFocusedActor)
//			{
//				if (CurrentFocusedActor)
//				{
//					CurrentFocusedActor->SetOutline(false); // 이전 액터 테두리 제거
//				}
//
//				CurrentFocusedActor = HitInteractionActor;
//				CurrentFocusedActor->SetOutline(true); // 현재 액터 테두리 표시
//				if (GEngine)
//				{
//					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Tracked!"));
//				}
//			}
//			return;
//		}
//	}
//
//	// 감지된 액터가 없을 경우
//	if (CurrentFocusedActor)
//	{
//		CurrentFocusedActor->SetOutline(false);
//		CurrentFocusedActor = nullptr;
//	}
//}

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

				// 새로운 액터 감지 시 outline 처리
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

		// 디버그 라인 그리기
		/*DrawDebugLine(
			GetWorld(),
			TraceStart,
			TraceEnd,
			bIsBaseInteractionActor ? FColor::Green : FColor::Red,
			false, 0.1f, 0, 2.0f
		);*/
	}
}

void ARevolutionPlayerController::HandleInteraction()
{
	if (!IsBasicMode) return;

	if (CurrentFocusedActor)
	{
		CurrentFocusedActor->OnInteract(); // 자식에서 오버라이드된 함수 실행
	}
}

void ARevolutionPlayerController::SetBasicMode(bool bEnable)
{
	IsBasicMode = bEnable ? 1 : 0;

	bShowMouseCursor = !bEnable;
	bEnableClickEvents = !bEnable;
	bEnableMouseOverEvents = !bEnable;

	// 기본모드로 전환 시 HUD 조준점 등 복구 로직 추가 가능
}