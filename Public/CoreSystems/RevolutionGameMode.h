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
	UGPTManager* Suspect1GPT;

	UPROPERTY()
	UGPTManager* Suspect2GPT;

	UPROPERTY()
	UGPTManager* Suspect3GPT;

protected:
	virtual void BeginPlay() override;

public:
	ARevolutionGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	bool IsInitMode = false;

	UPROPERTY()
	UGPTManager* SelectedGPT;

	UPROPERTY()
	int32 SelectedNumber;

	UFUNCTION(BlueprintCallable)
	void SaveInputString(const FString& input);

	UFUNCTION(BlueprintCallable)
	void AskSuspect(const FString& Question);

	UFUNCTION(BlueprintCallable)
	void OnSuspectResponse(const FString& Response);

	UFUNCTION(BlueprintCallable)
	void SetSelectedSuspect(int32 value);

	UFUNCTION()
	void doInit();

	UFUNCTION(BlueprintCallable)
	void InitGPT(FString key);


	
};
