// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class MYPROJECT_API SWidgetMyClass : public SCompoundWidget
{
public:
	

	/*needs to use SLATE_BEGIN_ARGS and SLATE_END_ARS to add support for SNew and SAssignNew
	Creating a Widget without doing it in blue print*/

	//Declaring the SWidgetMyClass into the Blueprint using this Macro
	SLATE_BEGIN_ARGS(SWidgetMyClass) {}

	// Declaring OwningHUDArg pointer into the Blueprint using the SLATE ARGUMENT Macro
	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUDArg)

	SLATE_END_ARGS()

	// Every Widget needs a construction function
	void Construct(const FArguments& InArgs);
	
	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	/*The reason why 2 pointers from the same class is needed
	OwningHUD has to be valid in order for the play and quit buttons to work,
	I had to make OwningHUD = OwningHUDArgs because, I really want to say is if the pointer in the blueprint is valid
	Then the click buttons will work. OwningHUDArgs gets valid in MyHUD.cpp line 33.
	This is basically saying if OwningHUDArgs in the blueprint is valid the buttons will work,
	this is one of many ways to create a widget without doing it in blue print, I learned this online, there are easier ways now*/

	TWeakObjectPtr<class AMyHUD> OwningHUD;

	// Tells our widget that it does support keyboard function, if I don't do this I'll get an annoying error message
	virtual bool SupportsKeyboardFocus() const override { return true; };

};
