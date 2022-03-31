// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
		// Step 2 add these three below and then go to MyHUD.cpp
protected:
	TSharedPtr<class SWidgetMyClass> MenuWidget; // store refr to the menu itself
	TSharedPtr<class SWidget> MenuWidgetContainer; // use the container to remove and add the menu to the screen

	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();
	
};
