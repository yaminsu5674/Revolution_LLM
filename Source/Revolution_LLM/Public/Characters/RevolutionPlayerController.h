// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"  // �߰�
#include "InputMappingContext.h" // �߰�
#include "InputAction.h"        // �߰�
#include "EnhancedInputComponent.h" // �߰�
#include "EnhancedInputSubsystems.h" // �߰�
#include "RevolutionPlayerController.generated.h"

UCLASS()
class REVOLUTION_LLM_API ARevolutionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARevolutionPlayerController();

protected:
	// ���� ��� (1: �⺻ ����Ʈ���̽� ��� / 0: ���콺 ���ͷ��� ���)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mode")
	int32 IsBasicMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	// HUD �� Input UI
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* Input;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InputClass;

	// ���� ����Ʈ���̽��� ������ ����
	UPROPERTY()
	class ABaseInteractionActor* CurrentFocusedActor;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	// ����Ʈ���̽� ó�� (������ ���)
	void TraceFromCrosshair();

	// ���ͷ��� ���� �Լ�
	void HandleInteraction();

	// ���ͷ��� ��� ��ȯ �Լ� (�ܺο����� ������ �� �ֵ��� public���� ��� ��)
	void SetBasicMode(bool bEnable);
};