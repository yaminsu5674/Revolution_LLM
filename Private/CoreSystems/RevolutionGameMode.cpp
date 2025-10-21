// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/RevolutionGameMode.h"
#include "CoreSystems/RevolutionGameInstance.h"
#include "Characters/RevolutionPlayerController.h"
#include "Kismet/GameplayStatics.h"

ARevolutionGameMode::ARevolutionGameMode()
{

	PlayerControllerClass = ARevolutionPlayerController::StaticClass(); 
}

void ARevolutionGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void ARevolutionGameMode::SaveInputString(const FString& input)
{
	InputString = input;

	AskSuspect(InputString);
}

void ARevolutionGameMode::AskSuspect(const FString& Question)
{

	if (SelectedGPT)
	{
		SelectedGPT->SendMessageToGPT(Question, [this](const FString& Response)
			{
				OnSuspectResponse(Response);
			});
	}
}

void ARevolutionGameMode::OnSuspectResponse(const FString& Response)
{
	UE_LOG(LogTemp, Log, TEXT("Suspect says: %s"), *Response);

	if (UWorld* World = GetWorld())
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (ARevolutionPlayerController* RevPC = Cast<ARevolutionPlayerController>(PC))
		{
			if (UUserWidget** FoundWidget = RevPC->WidgetManager->WidgetMap.Find("Output"))
			{
				if (UOutputWidget* OutputWidget = Cast<UOutputWidget>(*FoundWidget))
				{
					AsyncTask(ENamedThreads::GameThread, [OutputWidget, Response]()
						{
							OutputWidget->UpdateOutputText(Response);
						});
				}
			}
		}
	}
}

void ARevolutionGameMode::SetSelectedSuspect(int32 value)
{
	if (value == 1)
	{
		SelectedGPT = Suspect1GPT;
		SelectedNumber = 1;
	}
	else if (value == 2)
	{
		SelectedGPT = Suspect2GPT;
		SelectedNumber = 2;
	}
	else if (value == 3)
	{
		SelectedGPT = Suspect3GPT;
		SelectedNumber = 3;
	}
}

void ARevolutionGameMode::doInit()
{

	const FString SharedContext = TEXT(
		"This is a high - profile murder case involving the death of Dr.Dohyun Lee, a respected professor in biochemical engineering. "
		"Three key individuals are being interrogated: Kang Minseok (a postdoctoral researcher and mentee), Professor Sangjin Kim (a senior academic rival), and Ji-eun Yoon (the victim's wife). "
		"Each suspect has a motive, personal history with the victim, and emotional stakes in the case. "
		"All suspects are aware of each other's identities, relationships with the victim, and the fact that they are being investigated simultaneously."
	);

	Suspect1GPT->InitializePrompt(FString::Printf(TEXT(
		"%s "
		"You are Suspect 1: Kang Minseok, a postdoctoral researcher in biochemical engineering. "
		"Outwardly calm and logical, you are meticulous and articulate. However, beneath your composed exterior lies anxiety, guilt, and inner turmoil. "
		"You are hiding a terrible truth about the murder of your advisor, Dr. Dohyun Lee. "
		"You had a close but tense relationship with the victim and felt pressured by his expectations. "
		"You know that Professor Kim had argued with Dr. Lee that day, and that Ji-eun, his wife, left after a heated fight. "
		"When questioned, maintain a precise and respectful tone, but when pushed emotionally, your sentences may falter or become slightly inconsistent. "
		"You sometimes bite your nails when stressed. Avoid outright confessions, but let subtle inconsistencies or slip-ups hint at your guilt."
	), *SharedContext));

	Suspect2GPT->InitializePrompt(FString::Printf(TEXT(
		"%s "
		"You are Suspect 2: Professor Sangjin Kim, a veteran environmental engineering professor and former mentor of Dr. Dohyun Lee. "
		"You are proud, emotionally intense, and have a short temper when your authority is questioned. "
		"You had a public argument with the victim on the day of the murder and initially lied about visiting his house, which raises suspicions. "
		"You know Kang Minseok is the victim's prot?g?, and Ji-eun is the grieving widow. "
		"You often emphasize your long academic experience and get defensive when accused. "
		"Deny any involvement in the murder, but your anger and ego may cause you to say things that deepen suspicion unintentionally."
	), *SharedContext));

	Suspect3GPT->InitializePrompt(FString::Printf(TEXT(
		"%s "
		"You are Suspect 3: Ji-eun Yoon, the wife of Dr. Dohyun Lee. "
		"You are emotionally sensitive and still in shock from discovering your husband's body. "
		"You recently had a major argument with him and stormed out of the house, which makes you look suspicious. "
		"You know that Kang Minseok was your husband's close student, and that Professor Kim had a difficult professional relationship with him. "
		"You are not guilty, but your grief, guilt, and confusion cause you to answer inconsistently and emotionally. "
		"You might cry, stammer, or express mixed emotions during the interrogation. "
		"Do not fabricate stories, but allow your trauma and emotional state to affect your memory and speech patterns."
	), *SharedContext));
}


void ARevolutionGameMode::InitGPT(FString key)
{
	if (URevolutionGameInstance* MyGI = Cast<URevolutionGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGI->SpawnSuspects();
	}
	Suspect1GPT = NewObject<UGPTManager>(this, UGPTManager::StaticClass());
	Suspect2GPT = NewObject<UGPTManager>(this, UGPTManager::StaticClass());
	Suspect3GPT = NewObject<UGPTManager>(this, UGPTManager::StaticClass());

	if (Suspect1GPT)
	{
		Suspect1GPT->LoadApiKey(key);
	}
	if (Suspect2GPT)
	{
		Suspect2GPT->LoadApiKey(key);
	}
	if (Suspect3GPT)
	{
		Suspect3GPT->LoadApiKey(key);
	}


	if (IsInitMode)
	{
		doInit();
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Not initialized!"));
		}
	}
}