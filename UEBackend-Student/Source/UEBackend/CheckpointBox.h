// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckpointBox.generated.h"

/**
 * 
 */
UCLASS()
class UEBACKEND_API ACheckpointBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACheckpointBox();


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//class AServerConnect* ServerCommunicator;

	UPROPERTY(EditAnywhere, Category="Checkpoint Name")
	FString CheckpointName;


protected:
	void Tick(float DeltaTime) override;

	// To add mapping context
	virtual void BeginPlay() override;
};
