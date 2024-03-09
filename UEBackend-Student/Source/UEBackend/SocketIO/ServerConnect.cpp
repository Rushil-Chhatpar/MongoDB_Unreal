// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerConnect.h"
#include "SocketIOClientComponent.h"
#include "SIOJson/Public/SIOJsonValue.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
//#include  "PlayerControllerMultiplayer.h"
// Sets default values
AServerConnect::AServerConnect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SocketIOComponent = CreateDefaultSubobject<USocketIOClientComponent>("SocketIO Component");
	IpAddress = "http://127.0.0.1:8000";
}

// Called when the game starts or when spawned
void AServerConnect::BeginPlay()
{
	Super::BeginPlay();
	//if(AutoConnect)
	Connect();

	SocketIOComponent->OnNativeEvent(TEXT("chat"), [this](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			ReceiveMessage(Message);
		});
	SocketIOComponent->OnNativeEvent(TEXT("getlastcp"), [this](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			ReceiveCheckPoint(Message);
		});

	  // SendMessage(FString("Hello From Unreal"));

	SendGetLastCheckPoint();
	SendStruct();
}

void AServerConnect::Connect()
{
	SocketIOComponent->Connect(IpAddress);
	

}

//void AServerConnect::QueueUp(FString map, FString name)
void AServerConnect::SendMessage(FString Message)
{
	//auto JSONObject = USIOJConvert::MakeJsonObject();
	TSharedPtr<FJsonObject> JSONObject = MakeShareable(new FJsonObject);
	JSONObject->SetStringField(TEXT("name"), PlayerName);
	JSONObject->SetStringField(TEXT("message"), Message);
	// Send the JSON data to chat event
	SocketIOComponent->EmitNative(TEXT("chat"), JSONObject);
}

void AServerConnect::SendCheckPoint(FString cpName)
{
	TSharedPtr<FJsonObject> JSONObject = MakeShareable(new FJsonObject);
	JSONObject->SetStringField(TEXT("player"), PlayerName);
	JSONObject->SetStringField(TEXT("checkpoint"), cpName);
	// Send the JSON data to save event
	SocketIOComponent->EmitNative(TEXT("save"), JSONObject);
}

void AServerConnect::SendGetLastCheckPoint()
{
	TSharedPtr<FJsonObject> JSONObject = MakeShareable(new FJsonObject);
	JSONObject->SetStringField(TEXT("player"), PlayerName);
	// Send the JSON data to getlastcp event
	SocketIOComponent->EmitNative(TEXT("getlastcp"), JSONObject);
}

void AServerConnect::SendStruct()
{
}

void AServerConnect::ReceiveStruct(const TSharedPtr<FJsonValue>& Message)
{
}

void AServerConnect::ReceiveCheckPoint(const TSharedPtr<FJsonValue>& Message)
{
	TSharedPtr<FJsonObject> JSONObject = Message->AsObject();
	FString lastCPName = JSONObject->GetStringField("name");
	if(!lastCPName.IsEmpty())
	{
		TArray<AActor*> checkpoints;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(lastCPName), checkpoints);
		if(!checkpoints.IsEmpty())
		{
			GetWorld()->GetFirstPlayerController()->GetPawn()->TeleportTo(checkpoints[0]->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

void AServerConnect::ReceiveMessage(const TSharedPtr<FJsonValue>& Message)
{
	TSharedPtr<FJsonObject> JSONObject = Message->AsObject();
	//FString baseStr = UKismetStringLibrary::Concat_StrStr(JSONObject->GetStringField("name") + " : ", JSONObject->GetStringField("message"));
	FString baseStr = JSONObject->GetStringField("name") + " : " + JSONObject->GetStringField("message");
	if(!baseStr.IsEmpty())
	{
		ChatQueue.Enqueue(baseStr);
	}
}

FString AServerConnect::GetNextMessageInQueue()
{
	if (!ChatQueue.IsEmpty())
	{
		FString message;
		if (ChatQueue.Peek(message))
		{
			if(!message.IsEmpty())
			{
				if (ChatQueue.Pop())
				{
					return message;
				}
			}
		}
	}

	

	return FString("NULL");
}

void AServerConnect::SendAbility(FString playerName, FString AbilityName, FString IconPath)
{
	TSharedPtr<FJsonObject> JSONObject = MakeShareable(new FJsonObject);
	JSONObject->SetStringField("playerName", PlayerName);
	JSONObject->SetStringField("abilityName", AbilityName);
	JSONObject->SetStringField("iconPath", IconPath);
	// Send the JSON data to addability event
	SocketIOComponent->EmitNative("addability", JSONObject);
}

