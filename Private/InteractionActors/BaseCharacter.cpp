// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	// SkeletalMeshComponent를 생성하고 기본 루트로 설정
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMesh);

	if (SkeletalMesh)
	{
		SkeletalMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

		SkeletalMesh->SetRenderCustomDepth(false);
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 필요 시 여기서 초기화
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::OnInteract()
{
	Super::OnInteract();
	// 필요시 캐릭터 전용 상호작용
}

void ABaseCharacter::SetOutline(bool bEnable)
{
	if (!SkeletalMesh) return;

	if (bEnable && HighlightMaterial)
	{
		OriginalMaterial = SkeletalMesh->GetMaterial(0);
		SkeletalMesh->SetMaterial(0, HighlightMaterial);
	}
	else if (OriginalMaterial)
	{
		SkeletalMesh->SetMaterial(0, OriginalMaterial);
	}
}

