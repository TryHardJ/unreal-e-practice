// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpawnLevel.h"
#include "MyBaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
AMySpawnLevel::AMySpawnLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMySpawnLevel::BeginPlay()
{
	Super::BeginPlay();
	SpawnLevel(true);
	/*SpawnLevel(false); not sure why he made three false in the video, will check this out myself
	SpawnLevel(false);
	SpawnLevel(false);*/

	
}

// Called every frame
void AMySpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AMySpawnLevel::SpawnLevel(bool IsFirst)
{
	SpawnLocation = FVector(1300.0f, 0.0f, 0.f); // 
	SpawnRotation = FRotator(0, 0, 0); //

	if (!IsFirst)
	{
		AMyBaseLevel* LastLevel = LevelList.Last(); // getting the last level from the arraylist, LastLevel is the pointing to the LevelList Array
		
		SpawnLocation = LastLevel->GetSapwnLocation()->GetComponentTransform().GetTranslation(); // returns the position of our spawn location
		// mybaselevel.cpp returns spawn location and the blueprint event graph sets the spawn location to equal a spawn location box that we use in the viewport
		// SpawnLocation gets the value of the last position and from there we know were the last level is
	}

	RandomLevel = FMath::RandRange(1, 6); // picking levels 1 through 10, only create 1 level so far
	AMyBaseLevel* NewLevel = nullptr;

	if (RandomLevel == 1) // If the random level is == to 1
	{
		//get the world and from the world spawn an actor, which is a type of base level, we will spawn the level 1 actor, at the spawn location with spawn rotation and spawn info
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level1, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 2) 
	{	
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level2, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 3) 
	{
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level3, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 4) 
	{
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level4, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 5) 
	{
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level5, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 6) 
	{
		NewLevel = GetWorld()->SpawnActor<AMyBaseLevel>(Level6, SpawnLocation, SpawnRotation, SpawnInfo);
	}


	if (NewLevel) {
		if (NewLevel->GetTrigger()) // if the trigger is passed by on the new level, spawn new levels. Trigger that I'm creating in mybaselevel.cpp, used it in blueprint for event graph and viewport
		{
			NewLevel->GetTrigger()->OnComponentBeginOverlap.
				AddDynamic(this, &AMySpawnLevel::OnOverlapBegin); // assign a function that will begin when we overlap the trigger
		}
	}

	LevelList.Add(NewLevel); //adding new level to list array
	if (LevelList.Num() > 5) // not allowing more than five elements inside the level
	{
		LevelList.RemoveAt(0); 
	}

}


void AMySpawnLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// pass through the spawnlevel function all over again
{
	SpawnLevel(false);
}


