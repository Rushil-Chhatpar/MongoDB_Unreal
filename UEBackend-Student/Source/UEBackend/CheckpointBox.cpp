// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointBox.h"

#include "BEGameInstance.h"
#include "Components/ShapeComponent.h"
#include "DrawDebugHelpers.h"
#include "ServerConnect.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
ACheckpointBox::ACheckpointBox()
{
    PrimaryActorTick.bCanEverTick = true;
    // Ensure the root component is set to generate overlap events
    GetCollisionComponent()->SetGenerateOverlapEvents(true);

    // Set the collision profile to trigger
    GetCollisionComponent()->SetCollisionProfileName(TEXT("OverlapAll"));

    // Register to the OnComponentBeginOverlap and OnComponentEndOverlap events
    GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointBox::OnOverlapBegin);

   
}

void ACheckpointBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Handle overlap begin event
    if (OtherActor && (OtherActor != this))
    {
        // Do something when an actor begins overlapping this trigger box
        UE_LOG(LogTemp, Warning, TEXT("Overlap Begins with %s"), *OtherActor->GetName());
        if(OtherActor->IsA<ACharacter>())
        {
	        if(GetGameInstance<UBEGameInstance>()->ServerCommunicator)
	        {
                GetGameInstance<UBEGameInstance>()->ServerCommunicator->SendCheckPoint(CheckpointName);
	        }
        }
    }
}

void ACheckpointBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugBox(GetWorld(), GetActorLocation(), GetCollisionComponent()->Bounds.BoxExtent, FColor::Green, false, -1.0f, 0, 5);
}

void ACheckpointBox::BeginPlay()
{
	Super::BeginPlay();

    Tags.Add( FName( CheckpointName));

    GetGameInstance<UBEGameInstance>()->ServerCommunicator = Cast<AServerConnect>(UGameplayStatics::GetActorOfClass(GetWorld(), AServerConnect::StaticClass()));
}
