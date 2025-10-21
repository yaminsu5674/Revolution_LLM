// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoreSystems/RevolutionGameMode.h"
#include "InputActionValue.h"  
#include "InputMappingContext.h" 
#include "InputAction.h"        
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "Widget/OutputWidget.h"
#include "Widget/WidgetManager.h"
#include "RevolutionPlayerController.generated.h"

UENUM(BlueprintType)
enum class EGameUIMode : uint8
{
	Lobby,
	Normal,
	Talk,
	Computer,
	CaseEnd,
	End
};

UCLASS()
class REVOLUTION_LLM_API ARevolutionPlayerController : public APlayerController
{
	GENERATED_BODY()

	ARevolutionGameMode* RevGameMode;

	int32 Choice;

	EGameUIMode UIMode = EGameUIMode::Lobby;

public:
	ARevolutionPlayerController();

	UPROPERTY(EditAnywhere, Category = "Manager")
	TSubclassOf<UWidgetManager> WidgetManagerClass;

	UPROPERTY()
	UWidgetManager* WidgetManager;

	UFUNCTION(BlueprintCallable)
	void SetGameUIMode(EGameUIMode NewMode);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY()
	class ABaseInteractionActor* CurrentFocusedActor;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	void SetMouse(bool bEnable);

	void TraceFromCrosshair();

	void HandleInteraction();

	UFUNCTION(BlueprintCallable)
	void SubmitResult(int32 value);
};

