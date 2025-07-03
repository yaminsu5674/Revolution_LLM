// Copyright Epic Games, Inc. All Rights Reserved.

#include "InteractionActors/BaseInteractionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Engine.h"

ABaseInteractionActor::ABaseInteractionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	

	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // �߿�!

	// �׵θ� ȿ���� Custom Depth Ȱ��ȭ (������ ������ PostProcess�� Outline ó�� ����)
	Mesh->SetRenderCustomDepth(false); // �⺻�� ��Ȱ��ȭ


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightMatFinder(TEXT("/Game/Static/LevelPrototyping/Materials/MI_Solid_Blue"));
	if (HighlightMatFinder.Succeeded())
	{
		HighlightMaterial = HighlightMatFinder.Object;
	}
}

void ABaseInteractionActor::BeginPlay()
{
	Super::BeginPlay();

	OriginalMaterial = Mesh->GetMaterial(0);
}

void ABaseInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractionActor::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseInteractionActor interacted!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interacted with BaseInteractionActor"));
	}
}

void ABaseInteractionActor::SetOutline(bool bEnable)
{
	if (HighlightMaterial && bEnable)
	{
		//Mesh->SetMaterial(0, HighlightMaterial);
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue(1);
	}
	else if (OriginalMaterial && !bEnable)
	{
		//Mesh->SetMaterial(0, OriginalMaterial);
		Mesh->SetRenderCustomDepth(false);
	}
}