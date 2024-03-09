// Fill out your copyright notice in the Description page of Project Settings.


#include "Scroll.h"

#include "UEBackendCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AScroll::AScroll()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionProfileName("NoCollision");

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
	Collider->SetCollisionProfileName("OverlapAllDynamic");

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::AScroll::OnBeginOverlao);

}

// Called when the game starts or when spawned
void AScroll::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScroll::OnBeginOverlao(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		AUEBackendCharacter* Player = Cast<AUEBackendCharacter>(OtherActor);
		if(Player)
		{
			Player->AddAbility(AbilityName, IconPath);
		}
	}
	Destroy();
}

// Called every frame
void AScroll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

