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
	Mesh->SetRenderCustomDepth(true); // 테두리 효과 위해

	// 마우스 이벤트 바인딩
	Mesh->OnBeginCursorOver.AddDynamic(this, &ABaseInteractionActor::OnBeginCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &ABaseInteractionActor::OnEndCursorOver);
	Mesh->OnClicked.AddDynamic(this, &ABaseInteractionActor::OnClicked);
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

void ABaseInteractionActor::OnBeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
	if (HighlightMaterial)
	{
		Mesh->SetMaterial(0, HighlightMaterial);
	}
}

void ABaseInteractionActor::OnEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	if (OriginalMaterial)
	{
		Mesh->SetMaterial(0, OriginalMaterial);
	}
}

void ABaseInteractionActor::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnInteract();
}

void ABaseInteractionActor::OnInteract()
{
	// 여기서 자식 클래스에서 override 가능하게 기본 동작 구현
	UE_LOG(LogTemp, Warning, TEXT("BaseInteractionActor interacted!"));

	// 혹은 GEngine->AddOnScreenDebugMessage 사용 가능
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interacted with BaseInteractionActor"));
	}
}