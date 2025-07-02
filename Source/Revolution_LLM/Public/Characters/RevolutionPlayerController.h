// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RevolutionPlayerController.generated.h"

/**
 * 
 */
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
	
};
