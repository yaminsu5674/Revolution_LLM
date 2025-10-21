// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Suspect.h"

ASuspect::ASuspect()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASuspect::BeginPlay()
{
	Super::BeginPlay();

	// 필요 시 여기서 초기화
}

void ASuspect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuspect::OnInteract()
{
	Super::OnInteract();
	// 필요시 캐릭터 전용 상호작용
}