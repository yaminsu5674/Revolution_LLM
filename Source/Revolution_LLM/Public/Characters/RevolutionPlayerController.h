// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"  
#include "InputMappingContext.h" 
#include "InputAction.h"        
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "RevolutionPlayerController.generated.h"

UCLASS()
class REVOLUTION_LLM_API ARevolutionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARevolutionPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mode")
	int32 IsBasicMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mode")
	int32 IsInputMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	// HUD , Input UI
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* Input;

	UPROPERTY()
	UUserWidget* Exit;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InputClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> ExitClass;

	UPROPERTY()
	class ABaseInteractionActor* CurrentFocusedActor;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	void TraceFromCrosshair();

	void HandleInteraction();

	UFUNCTION(BlueprintCallable)
	void SetBasicMode(bool bEnable = true);
};