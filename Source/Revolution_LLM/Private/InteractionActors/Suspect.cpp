// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActors/Suspect.h"

ASuspect::ASuspect()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASuspect::BeginPlay()
{
	Super::BeginPlay();

	// �ʿ� �� ���⼭ �ʱ�ȭ
}

void ASuspect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuspect::OnInteract()
{
	Super::OnInteract();
	// �ʿ�� ĳ���� ���� ��ȣ�ۿ�
}