// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OutputWidget.h"
#include "Components/TextBlock.h"

void UOutputWidget::UpdateOutputText(const FString& NewText)
{
	if (OutputText)
	{
		OutputText->SetText(FText::FromString(NewText));
	}
}

void UOutputWidget::SetNameText(const FString& NewName)
{
	if (NameText)
	{
		NameText->SetText(FText::FromString(NewName));
	}
}