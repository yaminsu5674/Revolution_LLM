// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionActors/BaseInteractionActor.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class REVOLUTION_LLM_API ABaseCharacter : public ABaseInteractionActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMesh;

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	// ��ȣ�ۿ� �Լ� �������̵� ����
	virtual void OnInteract() override;

	virtual void SetOutline(bool bEnable) override;
	
};
