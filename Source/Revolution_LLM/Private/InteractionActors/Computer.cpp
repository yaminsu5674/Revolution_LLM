// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Computer.h"

void AComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AComputer::OnInteract()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Computer Widget"));
	}

	// camera move and show the senario
}