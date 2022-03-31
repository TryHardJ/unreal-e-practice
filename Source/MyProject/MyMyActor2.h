// Fill out your copyright notice in the Description page of Project Settings.
// wall, ended up not using a wall that chases me, this class is useless 
#pragma once

#include "CoreMinimal.h"
#include "MyActor2.h"
#include "MyMyActor2.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyMyActor2 : public AMyActor2
{
	GENERATED_BODY()

public:
	AMyMyActor2();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
};
