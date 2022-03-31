// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseLevel.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyBaseLevel::AMyBaseLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyBaseLevel::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
	
}

// Called every frame
void AMyBaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* AMyBaseLevel::GetTrigger()
{
	return Trigger;
}

UBoxComponent* AMyBaseLevel::GetSapwnLocation()
{
	return SpawnLocation;
}


