// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "SWidgetMyClass.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	// Step 3 is to include SWidgetMyClass.h and Widgets/SWeakWidget.h and Engine/Engine.h and then everything under this

	/*if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SWidgetMyClass).OwningHUD(this); // had to add .OwningHUD to pass the hud class into the widget, passed SBallGameCompoundWidget as a variable

		// same as snew but it stores it in a variable
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef())); //MenuWidgetContainer, then creating a SWeakWidget with PossiblyNullContent
		// PossiblyNullContent is what we a passing in the Container
	}*/

	ShowMenu();
}


void AMyHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SWidgetMyClass).OwningHUDArg(this); // passing SWidgetyMyClass into the owninghudargs from SWidgetMyClass.h, basically adding it to the blueprint

		// Grab the game engine viewport, add viewport widget content, SAssignNew is using MenuWidgetContainer and creating a SWeakWidget, possiblyNull is what we are passing in the container,
		// because MenuWidet is a ref we have to type ToSharedRef
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

		if (PlayerOwner) // means we can only click on the ui and show our mouse cursor 
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMyHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

