// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseLevel.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyBaseLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBaseLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "My Triggers") // component trigger can be read and written, we can edit it inside of blueprint editor, fnd this component inside the blueprint category under My Triggers
		UBoxComponent* Trigger; // calling this pointer a trigger

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "My Triggers")
		UBoxComponent* SpawnLocation;

public:
	UBoxComponent* GetTrigger();
	UBoxComponent* GetSapwnLocation();
};
