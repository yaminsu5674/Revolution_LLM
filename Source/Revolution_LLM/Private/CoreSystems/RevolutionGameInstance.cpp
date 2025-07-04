// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/RevolutionGameInstance.h"
#include "InteractionActors/Suspect.h"


void URevolutionGameInstance::SpawnSuspects()
{
	UWorld* World = GetWorld();
	if (!World) return;

	const FString Suspect1Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect1.BP_Suspect1_C'");
	const FString Suspect2Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect2.BP_Suspect2_C'");
	const FString Suspect3Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect3.BP_Suspect3_C'");

	UClass* SuspectClass1 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect1Path));
	UClass* SuspectClass2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect2Path));
	UClass* SuspectClass3 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect3Path));

	if (SuspectClass1)
	{
		Suspect1 = World->SpawnActor<ASuspect>(SuspectClass1, Suspect1Location, SuspectRotation);
	}
	if (SuspectClass2)
	{
		Suspect2 = World->SpawnActor<ASuspect>(SuspectClass2, Suspect2Location, SuspectRotation);
	}
	if (SuspectClass3)
	{
		Suspect3 = World->SpawnActor<ASuspect>(SuspectClass3, Suspect3Location, SuspectRotation);
	}

	if (Suspect1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				TEXT("Suspect1 init")
			);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				TEXT("Not yet")
			);
		}
	}
}