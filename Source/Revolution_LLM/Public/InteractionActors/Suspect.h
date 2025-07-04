// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionActors/BaseCharacter.h"
#include "Suspect.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API ASuspect : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	ASuspect();

	virtual void Tick(float DeltaTime) override;

	// ��ȣ�ۿ� �Լ� �������̵� ����
	virtual void OnInteract() override;

	
};
