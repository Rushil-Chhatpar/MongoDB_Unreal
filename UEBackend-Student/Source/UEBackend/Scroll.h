// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scroll.generated.h"

UCLASS()
class UEBACKEND_API AScroll : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScroll();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, Category="Stats")
	FString AbilityName;

	UPROPERTY(EditAnywhere, Category = "Stats")
	FString IconPath = "RandomValue";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlao(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
