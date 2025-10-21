// Fill out your copyright notice in the Description page of Project Settings.

#include "GPT/GPTManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"

UGPTManager::UGPTManager()
{
    //LoadApiKey();
}

void UGPTManager::LoadApiKey(FString key)
{
    ApiKey = key;
}

void UGPTManager::InitializePrompt(const FString& SystemPrompt)
{
    MessageHistory.Empty();

    FChatMessage SystemMsg;
    SystemMsg.Role = "system";
    SystemMsg.Content = SystemPrompt;
    MessageHistory.Add(SystemMsg);
}

void UGPTManager::AddUserMessage(const FString& UserMessage)
{
    FChatMessage Msg;
    Msg.Role = "user";
    Msg.Content = UserMessage;
    MessageHistory.Add(Msg);
}

void UGPTManager::AddAssistantMessage(const FString& AssistantMessage)
{
    FChatMessage Msg;
    Msg.Role = "assistant";
    Msg.Content = AssistantMessage;
    MessageHistory.Add(Msg);
}

void UGPTManager::SendMessageToGPT(const FString& UserMessage, TFunction<void(const FString&)> Callback)
{
    AddUserMessage(UserMessage);
    bIsWaitingForResponse = true;

    // JSON 페이로드 생성
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    JsonObject->SetStringField("model", "gpt-3.5-turbo");

    TArray<TSharedPtr<FJsonValue>> MessagesJsonArray;
    for (const FChatMessage& Msg : MessageHistory)
    {
        TSharedPtr<FJsonObject> MsgObj = MakeShareable(new FJsonObject);
        MsgObj->SetStringField("role", Msg.Role);
        MsgObj->SetStringField("content", Msg.Content);
        MessagesJsonArray.Add(MakeShareable(new FJsonValueObject(MsgObj)));
    }
    JsonObject->SetArrayField("messages", MessagesJsonArray);

    FString PayloadString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&PayloadString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    MakeHttpRequest(PayloadString, [this, Callback](const FString& ResponseContent)
        {
            FString AssistantReply = TEXT("GPT API Key does not exist.");

            // Parse JSON
            TSharedPtr<FJsonObject> JsonParsed;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);
            if (FJsonSerializer::Deserialize(Reader, JsonParsed) && JsonParsed.IsValid())
            {
                const TArray<TSharedPtr<FJsonValue>>* ChoicesArray;
                if (JsonParsed->TryGetArrayField("choices", ChoicesArray) && ChoicesArray->Num() > 0)
                {
                    TSharedPtr<FJsonObject> MessageObj = (*ChoicesArray)[0]->AsObject()->GetObjectField("message");
                    FString Content = MessageObj->GetStringField("content");
                    AssistantReply = Content.TrimStartAndEnd();  // 혹시 모를 양쪽 공백 제거
                }
            }

            AddAssistantMessage(AssistantReply);
            LastAssistantReply = AssistantReply;
            bIsWaitingForResponse = false;

 

            Callback(AssistantReply);
        });
}

void UGPTManager::MakeHttpRequest(const FString& PayloadJson, TFunction<void(const FString&)> Callback)
{
    // HTTP 요청 보내는 기본 코드 (OpenAI API 호출)
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(TEXT("https://api.openai.com/v1/chat/completions"));
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
    Request->SetContentAsString(PayloadJson);

    Request->OnProcessRequestComplete().BindLambda(
        [Callback](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bWasSuccessful)
        {
            if (bWasSuccessful && Resp.IsValid())
            {
                Callback(Resp->GetContentAsString());
            }
            else
            {
                Callback(TEXT("Error: Request failed"));
            }
        }
    );

    Request->ProcessRequest();
}