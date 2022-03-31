// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyHUD.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &AMyPlayerController::OpenMenu); //OpenMenu is the name in the project settings(input) 
	}
}

void AMyPlayerController::OpenMenu()
{
	if (AMyHUD* MyMHUD = Cast<AMyHUD>(GetHUD())) /* this is a dynamic pointer, if APlayerController::GetHUD is a pointer for AHUD, this is inside PlayerController.h, 
												 thats why I can use it. this pointer returns MyHUD which allows MyMHUD to point to ShowMenu */
	{
		MyMHUD->ShowMenu(); // could not name this MyHUD, had to name it MyMHUD
	}
}
