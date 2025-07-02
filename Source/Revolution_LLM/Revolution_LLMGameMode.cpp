// Copyright Epic Games, Inc. All Rights Reserved.

#include "Revolution_LLMGameMode.h"
#include "Revolution_LLMCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARevolution_LLMGameMode::ARevolution_LLMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
