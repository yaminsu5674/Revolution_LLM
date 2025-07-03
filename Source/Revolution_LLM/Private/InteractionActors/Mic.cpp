// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Mic.h"

void AMic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMic::OnInteract()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Open Input Widget"));
	}
}