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

	// 필요 시 여기서 초기화
}

void APolice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APolice::OnInteract()
{
	Super::OnInteract();
	// 필요시 캐릭터 전용 상호작용
}


void APolice::SetFlag(int32 value)
{
	Flag = value;
}
