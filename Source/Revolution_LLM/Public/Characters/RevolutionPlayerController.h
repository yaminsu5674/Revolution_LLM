#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RevolutionPlayerController.generated.h"

UCLASS()
class REVOLUTION_LLM_API ARevolutionPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* Input;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InputClass;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// 클릭 시 실행될 라인트레이스 함수
	void HandleInteraction();
};