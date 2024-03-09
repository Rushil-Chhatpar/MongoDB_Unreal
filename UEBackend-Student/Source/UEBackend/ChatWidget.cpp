// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"

#include "BEGameInstance.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "ServerConnect.h"
#include "Kismet/GameplayStatics.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SendButton)
	{
		SendButton->OnClicked.AddDynamic(this, &UChatWidget::SendButtonClicked);
	}
}

bool UChatWidget::Initialize()
{
	bool Success = Super::Initialize();

	/*if (ChatMessages)
	{
		ChatMessages->TextDelegate.BindUFunction(this, "SetIncomingMessages");
	}*/

	//ServerCommunicator = Cast<AServerConnect>(UGameplayStatics::GetActorOfClass(GetWorld(), AServerConnect::StaticClass()) );

	//GetGameInstance<UBEGameInstance>()->ServerCommunicator->OnMessageReceived.AddUFunction(this, "OnMessageReceived");
	//ServerCommunicator->OnMessageReceived.AddUFunction(this,"OnMessageReceived");

	FTimerHandle MemberTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UChatWidget::SetIncomingMessages, 0.1f, true);


	ChatMessages->SetText(FText::FromString(""));

	return true;
}

//FText UChatWidget::SetIncomingMessages()
void UChatWidget::SetIncomingMessages()
{
	if(GetGameInstance<UBEGameInstance>()->ServerCommunicator)
	{
		FString message = GetGameInstance<UBEGameInstance>()->ServerCommunicator->GetNextMessageInQueue();
		if(!message.Contains("NULL"))
		{
			FString text = ChatMessages->GetText().ToString() + FString("\n") + message;
			//if(!text.Equals("NULL"))
	//		return FText::FromString(text);
			ChatMessages->SetText(FText::FromString(text));
		}
	}

	//return FText::FromString("NULL");
}

void UChatWidget::SendButtonClicked()
{
	if(GetGameInstance<UBEGameInstance>()->ServerCommunicator)
	{
		if (SendMessage)
		{
			GetGameInstance<UBEGameInstance>()->ServerCommunicator->SendMessage(SendMessage->GetText().ToString());
			
			SendMessage->SetText(FText::FromString(FString(""))) ;
		}
	}
}

void UChatWidget::OnMessageReceived(FString msg)
{
	FString text = ChatMessages->GetText().ToString() + FString("\n") + msg;
	ChatMessages->SetText(  FText::FromString(text));
}
