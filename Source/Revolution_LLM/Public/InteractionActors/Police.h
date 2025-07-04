// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionActors/BaseCharacter.h"
#include "Police.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API APolice : public ABaseCharacter
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Flag;

protected:
	virtual void BeginPlay() override;


public:
	APolice();

	virtual void Tick(float DeltaTime) override;

	// ��ȣ�ۿ� �Լ� �������̵� ����
	virtual void OnInteract() override;

	void SetFlag(int32 value);

	//void CallSuspects();

	
};
