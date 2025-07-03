#include "Characters/RevolutionPlayerController.h"
#include "CoreSystems/RevolutionGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractionActors/BaseInteractionActor.h" 

void ARevolutionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("PlayerController init"));
	}

	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;

	if (IsLocalController())
	{
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
}

void ARevolutionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &ARevolutionPlayerController::HandleInteraction);
}

void ARevolutionPlayerController::HandleInteraction()
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);

	FHitResult HitResult;
	if (GetHitResultAtScreenPosition(ScreenCenter, ECC_Visibility, true, HitResult))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()));

			// 예시: 인터랙션 인터페이스 또는 베이스클래스로 캐스팅
			if (ABaseInteractionActor* InteractionTarget = Cast<ABaseInteractionActor>(HitActor))
			{
				InteractionTarget->OnInteract(); // 너가 정의한 함수
			}
		}
	}
}