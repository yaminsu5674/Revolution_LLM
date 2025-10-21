// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Widget/OutputWidget.h"
#include "WidgetManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REVOLUTION_LLM_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<FName, UUserWidget*> WidgetMap;

	UPROPERTY()
	TMap<FName, TSubclassOf<UUserWidget>> WidgetClassMap;

    void Initialize(APlayerController* PC);

    void ShowUI(FName UIName);

    void HideUI(FName UIName);

    void HideAll();

	void DebugPrintWidgetStatus(FName UIName);

private:
    UPROPERTY()
    APlayerController* OwningPC;

    void CreateAndAdd(FName Name, TSubclassOf<UUserWidget> WidgetClass);

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> LobbyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UOutputWidget> EndingClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> InputClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> ExitClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UOutputWidget> OutputClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> ComputerClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> CaseEndClass;

};
