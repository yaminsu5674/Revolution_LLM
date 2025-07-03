// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"  // 추가
#include "InputMappingContext.h" // 추가
#include "InputAction.h"        // 추가
#include "EnhancedInputComponent.h" // 추가
#include "EnhancedInputSubsystems.h" // 추가
#include "RevolutionPlayerController.generated.h"

UCLASS()
class REVOLUTION_LLM_API ARevolutionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARevolutionPlayerController();

protected:
	// 현재 모드 (1: 기본 라인트레이스 모드 / 0: 마우스 인터랙션 모드)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mode")
	int32 IsBasicMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	// HUD 및 Input UI
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* Input;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InputClass;

	// 현재 라인트레이스로 감지된 액터
	UPROPERTY()
	class ABaseInteractionActor* CurrentFocusedActor;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	// 라인트레이스 처리 (조준점 기반)
	void TraceFromCrosshair();

	// 인터랙션 실행 함수
	void HandleInteraction();

	// 인터랙션 모드 전환 함수 (외부에서도 접근할 수 있도록 public으로 열어도 됨)
	void SetBasicMode(bool bEnable);
};