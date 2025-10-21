// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InteractionActors/Suspect.h"
#include "RevolutionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API URevolutionGameInstance : public UGameInstance
{
	GENERATED_BODY()


	// test fofofofo

public:
	URevolutionGameInstance();


	UPROPERTY(EditAnywhere, Category = "Suspects")
	FVector Suspect1Location = FVector(210.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Suspects")
	FVector Suspect2Location = FVector(210.f, 30.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Suspects")
	FVector Suspect3Location = FVector(210.f, 60.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Suspects")
	FRotator SuspectRotation = FRotator(0.f, 90.f, 0.f);

	UPROPERTY()
	ASuspect* Suspect1 = nullptr;

	UPROPERTY()
	ASuspect* Suspect2 = nullptr;

	UPROPERTY()
	ASuspect* Suspect3 = nullptr;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspects")
	TSubclassOf<ASuspect> SuspectClass;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspects")

	TSubclassOf<ASuspect> Suspect1Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspects")

	TSubclassOf<ASuspect> Suspect2Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspects")

	TSubclassOf<ASuspect> Suspect3Class;


	UFUNCTION(BlueprintCallable)
	void SpawnSuspects();





	
};
