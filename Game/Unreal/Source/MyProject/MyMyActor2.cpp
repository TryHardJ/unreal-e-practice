// Fill out your copyright notice in the Description page of Project Settings.
// wall   didn't use this class

#include "MyMyActor2.h"

AMyMyActor2::AMyMyActor2()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyMyActor2::BeginPlay()
{
	Super::BeginPlay();
	this->GetRootComponent()->ComponentVelocity = FVector(0, 25, 0); // get root componet from blueprint and sets the Speed of the Actor
}

void AMyMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + FVector(0, 350 * DeltaTime, 0), true); // moving the actor by using its current location, multiplying the y
}