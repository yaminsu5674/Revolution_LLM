// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionActors/BaseInteractionActor.h"
#include "Mic.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API AMic : public ABaseInteractionActor
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract();
	
};
