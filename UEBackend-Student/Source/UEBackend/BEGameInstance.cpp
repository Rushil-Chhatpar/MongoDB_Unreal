// Fill out your copyright notice in the Description page of Project Settings.


#include "BEGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "ServerConnect.h"
void UBEGameInstance::Init()
{
	Super::Init();

	ServerCommunicator = Cast<AServerConnect>(UGameplayStatics::GetActorOfClass(GetWorld(), AServerConnect::StaticClass()));
}
