// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GPT/GPTManager.h"
#include "RevolutionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API ARevolutionGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString InputString;

	UPROPERTY(EditAnywhere)
	FString OutputString;

	UPROPERTY()
	UGPTManager* SelectedGPT = nullptr;

	UPROPERTY()
	UGPTManager* Suspect1GPT = nullptr;

	UPROPERTY()
	UGPTManager* Suspect2GPT = nullptr;

	UPROPERTY()
	UGPTManager* Suspect3GPT = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	ARevolutionGameMode();

	UFUNCTION(BlueprintCallable)
	void SaveInputString(const FString& input);



	
};
