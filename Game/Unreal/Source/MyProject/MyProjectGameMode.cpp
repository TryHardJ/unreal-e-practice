// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectBall.h"
#include "MyHUD.h"
#include "MyPlayerController.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our ball

	DefaultPawnClass = AMyProjectBall::StaticClass();

	// Step 1 to show the widget, include both hud and playercontroller class and add both of these, go to MyHUD.h
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();

}
