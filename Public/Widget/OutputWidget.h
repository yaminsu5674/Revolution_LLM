// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutputWidget.generated.h"

UCLASS()
class REVOLUTION_LLM_API UOutputWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** GPT 응답으로 텍스트 갱신 */
	UFUNCTION(BlueprintCallable)
	void UpdateOutputText(const FString& NewText);

	/** 초기 이름 텍스트 설정 (한번만 호출) */
	UFUNCTION(BlueprintCallable)
	void SetNameText(const FString& NewName);

protected:
	// 블루프린트에서 BindWidget으로 연결될 텍스트 박스
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OutputText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
};