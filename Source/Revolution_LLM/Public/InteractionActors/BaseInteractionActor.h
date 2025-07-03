// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractionActor.generated.h"

UCLASS()
class REVOLUTION_LLM_API ABaseInteractionActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseInteractionActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	// ������ ��Ƽ����
	UPROPERTY()
	UMaterialInterface* OriginalMaterial;

	// ���̶���Ʈ(�׵θ� ��)�� ��Ƽ����
	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* HighlightMaterial;

public:
	virtual void Tick(float DeltaTime) override;

	// �ڽ� Ŭ�������� override�� ���ͷ��� �Լ�
	virtual void OnInteract();

	// �׵θ� ȿ���� ����
	void SetOutline(bool bEnable);
};