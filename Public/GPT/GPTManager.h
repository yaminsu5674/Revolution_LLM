// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GPTManager.generated.h"

USTRUCT()
struct FChatMessage
{
    GENERATED_BODY()

    UPROPERTY()
    FString Role;   // "system", "user", "assistant"

    UPROPERTY()
    FString Content;
};

UCLASS()
class REVOLUTION_LLM_API UGPTManager : public UObject
{
    GENERATED_BODY()

public:
    UGPTManager();

    bool bIsWaitingForResponse = false;

    bool IsWaitingResponse() const { return bIsWaitingForResponse; }

    // 메시지 히스토리 (대화 컨텍스트)
    UPROPERTY()
    TArray<FChatMessage> MessageHistory;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FString LastAssistantReply;

    void LoadApiKey(FString key);

    // 최초 프롬프트 세팅
    void InitializePrompt(const FString& SystemPrompt);

    // 유저 질문 추가
    void AddUserMessage(const FString& UserMessage);

    // GPT 응답 추가
    void AddAssistantMessage(const FString& AssistantMessage);

    // GPT API 호출 (비동기)
    void SendMessageToGPT(const FString& UserMessage, TFunction<void(const FString&)> Callback);

private:
    FString ApiKey;

    // 내부에서 HTTP 요청 보내는 함수 (구현 파일에서 작성)
    void MakeHttpRequest(const FString& PayloadJson, TFunction<void(const FString&)> Callback);
};
