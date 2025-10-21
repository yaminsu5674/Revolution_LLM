// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/WidgetManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/Engine.h" 

void UWidgetManager::Initialize(APlayerController* PC)
{
    OwningPC = PC;

    if (LobbyClass)
        WidgetClassMap.Add("Lobby", LobbyClass);
    if (HUDClass)
        WidgetClassMap.Add("HUD", HUDClass);
    if (InputClass)
        WidgetClassMap.Add("Input", InputClass);
    if (OutputClass)
        WidgetClassMap.Add("Output", OutputClass);
    if (ComputerClass)
        WidgetClassMap.Add("Computer", ComputerClass);
    if (CaseEndClass)
        WidgetClassMap.Add("CaseEnd", CaseEndClass);
    if (EndingClass)
        WidgetClassMap.Add("Ending", EndingClass);
    if (ExitClass)
        WidgetClassMap.Add("Exit", ExitClass);
}

void UWidgetManager::CreateAndAdd(FName Name, TSubclassOf<UUserWidget> WidgetClass)
{
    if (!OwningPC || !WidgetClass) return;

    // 매번 새로 생성
    if (UUserWidget* Widget = CreateWidget(OwningPC, WidgetClass))
    {
        Widget->AddToViewport();
        WidgetMap.Add(Name, Widget);
    }
}

void UWidgetManager::ShowUI(FName UIName)
{
    if (WidgetMap.Contains(UIName))
    {
        if (UUserWidget* Widget = WidgetMap[UIName])
        {
            Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible
            );
            Widget->SetIsEnabled(true);
            Widget->SetFocus();

        }
    }
    else if (WidgetClassMap.Contains(UIName))
    {
        CreateAndAdd(UIName, WidgetClassMap[UIName]);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget %s not found in WidgetClassMap."), *UIName.ToString());
    }

    //DebugPrintWidgetStatus(UIName);
}

void UWidgetManager::HideUI(FName UIName)
{
    if (WidgetMap.Contains(UIName))
    {
        if (UUserWidget* Widget = WidgetMap[UIName])
        {
            Widget->SetVisibility(ESlateVisibility::Hidden);

        }
    }
}

void UWidgetManager::HideAll()
{
    TArray<FName> Keys;
    WidgetMap.GetKeys(Keys);

    for (FName Key : Keys)
    {
        HideUI(Key); // RemoveFromParent + Remove map
    }
}


void UWidgetManager::DebugPrintWidgetStatus(FName UIName)
{
    if (!WidgetMap.Contains(UIName)) return;

    UUserWidget* Widget = WidgetMap[UIName];
    if (!Widget) return;

    FString VisibilityStr;
    switch (Widget->GetVisibility())
    {
    case ESlateVisibility::Visible: VisibilityStr = TEXT("Visible"); break;
    case ESlateVisibility::Collapsed: VisibilityStr = TEXT("Collapsed"); break;
    case ESlateVisibility::Hidden: VisibilityStr = TEXT("Hidden"); break;
    case ESlateVisibility::HitTestInvisible: VisibilityStr = TEXT("HitTestInvisible"); break;
    case ESlateVisibility::SelfHitTestInvisible: VisibilityStr = TEXT("SelfHitTestInvisible"); break;
    default: VisibilityStr = TEXT("Other"); break;
    }

    bool bIsEnabled = false;
    if (UWidget* RootWidget = Widget->GetRootWidget())
    {
        bIsEnabled = RootWidget->GetIsEnabled();
    }

    bool bHasKeyboardFocus = false;
    TSharedPtr<SWidget> FocusedSlateWidget = FSlateApplication::Get().GetKeyboardFocusedWidget();
    if (FocusedSlateWidget.IsValid() && Widget->TakeWidget() == FocusedSlateWidget)
    {
        bHasKeyboardFocus = true;
    }

    FString DebugMessage = FString::Printf(
        TEXT("Widget: %s\nVisibility: %s\nEnabled: %s\nHasFocus: %s"),
        *UIName.ToString(),
        *VisibilityStr,
        bIsEnabled ? TEXT("True") : TEXT("False"),
        bHasKeyboardFocus ? TEXT("True") : TEXT("False")
    );


    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,                   // Key (-1이면 누적)
            50.0f,                // Duration in seconds
            FColor::Yellow,       // Text Color
            DebugMessage          // Message
        );
    }

}