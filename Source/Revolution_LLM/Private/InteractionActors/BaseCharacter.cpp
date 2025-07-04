// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	// SkeletalMeshComponent�� �����ϰ� �⺻ ��Ʈ�� ����
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

	// �ʿ� �� ���⼭ �ʱ�ȭ
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::OnInteract()
{
	Super::OnInteract();
	// �ʿ�� ĳ���� ���� ��ȣ�ۿ�
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

