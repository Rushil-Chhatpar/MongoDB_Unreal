// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UEBackendCharacter.h"
#include "GameFramework/Actor.h"
#include "Templates/SharedPointer.h"
#include "ServerConnect.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMessageReceivedEvent, FString)

USTRUCT()
struct FTestCppStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	float SomeNumber;

	UPROPERTY()
	FString Name;
};

UCLASS()
class UEBACKEND_API AServerConnect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AServerConnect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//UPROPERTY(VisibleAnywhere, Category = "SocketIO Connection")
	UPROPERTY(EditAnywhere, Category = "SocketIO Connection")
	class USocketIOClientComponent* SocketIOComponent;

	UPROPERTY(EditAnywhere, Category = "SocketIO Connection")
	FString IpAddress;

	UPROPERTY(EditAnywhere, Category = "SocketIO Connection")
	FString PlayerName;

	UPROPERTY(EditAnywhere, Category = "SocketIO Connection")
	int32 Character;

	UPROPERTY(EditAnywhere, Category = "SocketIO Connection")
	bool AutoConnect = false;

	//UFUNCTION(BlueprintCallable, Category = "ServerConnect")
	void Connect();

	//UFUNCTION(BlueprintCallable, Category = "ServerConnect")
	//void Connect(FString Map, FString PName, FString GM, int32 Char);

	UFUNCTION()
	void SendMessage(FString Message);

	void SendCheckPoint(FString cpName);

	void SendGetLastCheckPoint();

	void SendStruct();
	void ReceiveStruct(const TSharedPtr< class FJsonValue>& Message);

	void ReceiveCheckPoint(const TSharedPtr< class FJsonValue>& Message);

	//UFUNCTION()
	void ReceiveMessage( const TSharedPtr< class FJsonValue>& Message);

	FString GetNextMessageInQueue();

	TQueue<FString> ChatQueue;

	//UPROPERTY()
	FMessageReceivedEvent OnMessageReceived;


#pragma region Abilities

	void SendAbility(FString playerName, FString AbilityName, FString IconPath);

#pragma endregion

#pragma region Stats

public:
	void SendStats(FStatsStruct& PlayerStats);
	void SendGetStats();
	void ReceiveStats(const TSharedPtr< class FJsonValue>& Message);

#pragma  endregion

};
