// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Police.h"
#include "CoreSystems/RevolutionGameInstance.h"
#include "Kismet/GameplayStatics.h"


APolice::APolice()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APolice::BeginPlay()
{
	Super::BeginPlay();
	if (URevolutionGameInstance* MyGI = Cast<URevolutionGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGI->SpawnSuspects();
	}

	// �ʿ� �� ���⼭ �ʱ�ȭ
}

void APolice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APolice::OnInteract()
{
	Super::OnInteract();
	// �ʿ�� ĳ���� ���� ��ȣ�ۿ�
}


void APolice::SetFlag(int32 value)
{
	Flag = value;
}
