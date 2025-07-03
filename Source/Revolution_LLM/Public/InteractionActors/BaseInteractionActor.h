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

	// 원래의 머티리얼
	UPROPERTY()
	UMaterialInterface* OriginalMaterial;

	// 하이라이트(테두리 등)용 머티리얼
	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* HighlightMaterial;

public:
	virtual void Tick(float DeltaTime) override;

	// 자식 클래스에서 override할 인터랙션 함수
	virtual void OnInteract();

	// 테두리 효과를 설정
	void SetOutline(bool bEnable);
};