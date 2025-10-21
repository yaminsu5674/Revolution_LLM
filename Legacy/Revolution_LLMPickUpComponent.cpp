// Copyright Epic Games, Inc. All Rights Reserved.

#include "Revolution_LLMPickUpComponent.h"

URevolution_LLMPickUpComponent::URevolution_LLMPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void URevolution_LLMPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &URevolution_LLMPickUpComponent::OnSphereBeginOverlap);
}

void URevolution_LLMPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ARevolution_LLMCharacter* Character = Cast<ARevolution_LLMCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
