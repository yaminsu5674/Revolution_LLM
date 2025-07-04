// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/BaseInteractionCharacter.h"

// Sets default values
ABaseInteractionCharacter::ABaseInteractionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	GetMesh()->SetRenderCustomDepth(false);


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightMatFinder(TEXT("/Game/Static/LevelPrototyping/Materials/MI_Solid_Blue"));
	if (HighlightMatFinder.Succeeded())
	{
		HighlightMaterial = HighlightMatFinder.Object;
	}

}

// Called when the game starts or when spawned
void ABaseInteractionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseInteractionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseInteractionCharacter::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseInteractionActor interacted!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interacted with BaseInteractionActor"));
	}
}

void ABaseInteractionCharacter::SetOutline(bool bEnable)
{
	if (HighlightMaterial && bEnable)
	{
		//Mesh->SetMaterial(0, HighlightMaterial);
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(1);
	}
	else if (!bEnable)
	{
		//Mesh->SetMaterial(0, OriginalMaterial);
		GetMesh()->SetRenderCustomDepth(false);
	}
}
