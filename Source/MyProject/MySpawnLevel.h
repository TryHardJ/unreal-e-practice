// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnLevel.generated.h"

class AMyBaseLevel; // Added this class because there are levels we have to put in here

UCLASS()
class MYPROJECT_API AMySpawnLevel : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMySpawnLevel();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
		void SpawnLevel(bool IsFirst);//Meaning is this the first level we will spawn


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	APawn* Player; 

	UPROPERTY(EditAnywhere) // be able to edit it from the blueprint anywhere
		TSubclassOf<AMyBaseLevel> Level1;

	UPROPERTY(EditAnywhere) 
		TSubclassOf<AMyBaseLevel> Level2;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyBaseLevel> Level3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyBaseLevel> Level4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyBaseLevel> Level5;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyBaseLevel> Level6;

	TArray<AMyBaseLevel*> LevelList;

public:

	int RandomLevel;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

};
