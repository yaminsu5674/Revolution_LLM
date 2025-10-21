// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/RevolutionGameInstance.h"
#include "InteractionActors/Suspect.h"

URevolutionGameInstance::URevolutionGameInstance()
{
	// Suspect 1
	static ConstructorHelpers::FClassFinder<ASuspect> Suspect1BP(TEXT("/Game/Dynamic/Blueprints/Characters/BP_Suspect1"));
	if (Suspect1BP.Succeeded())
	{
		Suspect1Class = Suspect1BP.Class;
	}

	// Suspect 2
	static ConstructorHelpers::FClassFinder<ASuspect> Suspect2BP(TEXT("/Game/Dynamic/Blueprints/Characters/BP_Suspect2"));
	if (Suspect2BP.Succeeded())
	{
		Suspect2Class = Suspect2BP.Class;
	}

	// Suspect 3
	static ConstructorHelpers::FClassFinder<ASuspect> Suspect3BP(TEXT("/Game/Dynamic/Blueprints/Characters/BP_Suspect3"));
	if (Suspect3BP.Succeeded())
	{
		Suspect3Class = Suspect3BP.Class;
	}
}

//void URevolutionGameInstance::SpawnSuspects()
//{
//	UWorld* World = GetWorld();
//	if (!World) return;
//
//	const FString Suspect1Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect1.BP_Suspect1_C'");
//	const FString Suspect2Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect2.BP_Suspect2_C'");
//	const FString Suspect3Path = TEXT("Blueprint'/Game/Dynamic/Blueprints/Characters/BP_Suspect3.BP_Suspect3_C'");
//
//	UClass* SuspectClass1 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect1Path));
//	UClass* SuspectClass2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect2Path));
//	UClass* SuspectClass3 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Suspect3Path));
//
//	if (SuspectClass1)
//	{
//		Suspect1 = World->SpawnActor<ASuspect>(SuspectClass1, Suspect1Location, SuspectRotation);
//	}
//	if (SuspectClass2)
//	{
//		Suspect2 = World->SpawnActor<ASuspect>(SuspectClass2, Suspect2Location, SuspectRotation);
//	}
//	if (SuspectClass3)
//	{
//		Suspect3 = World->SpawnActor<ASuspect>(SuspectClass3, Suspect3Location, SuspectRotation);
//	}
//
//}

void URevolutionGameInstance::SpawnSuspects()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (Suspect1Class)
	{
		Suspect1 = World->SpawnActor<ASuspect>(Suspect1Class, Suspect1Location, SuspectRotation);
	}

	if (Suspect2Class)
	{
		Suspect2 = World->SpawnActor<ASuspect>(Suspect2Class, Suspect2Location, SuspectRotation);
	}

	if (Suspect3Class)
	{
		Suspect3 = World->SpawnActor<ASuspect>(Suspect3Class, Suspect3Location, SuspectRotation);
	}
}