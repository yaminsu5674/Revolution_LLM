#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractionActor.generated.h"

UCLASS()
class REVOLUTION_LLM_API ABaseInteractionActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractionActor();

protected:
	virtual void BeginPlay() override;

	// Mesh for interaction object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	// Original material to revert back
	UPROPERTY()
	UMaterialInterface* OriginalMaterial;

	// Highlight material to apply on hover
	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* HighlightMaterial;

public:
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	virtual void OnInteract();

	UFUNCTION()
	void OnBeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};