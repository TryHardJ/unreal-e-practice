// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidgetMyClass.h"
#include "MyHUD.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/Layout/SBackgroundBlur.h"


#define LOCTEXT_NAMESPACE "MainMenu" // LOCTEXT is Unreal Engines Localization System, we replace text with whatever language is needed 

void SWidgetMyClass::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true; // advoids annoy error message

	OwningHUD = InArgs._OwningHUDArg;

	const FMargin ContentPadding = FMargin(130.f, 400.f, 0.f, 0.f);
	const FMargin ButtonPadding = FMargin(20.f);
	

	const FText TitleText = LOCTEXT("GameTitle", "Ball Game");
	const FText PlayText = LOCTEXT("PlayGame", "Play");
	const FText SettingsText = LOCTEXT("Settings", "Settings");
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 30.f;
	
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 40.f;

	// Stuff that you would do in blue print (drag drop), just doing it in c++ now
	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBackgroundBlur)
				.BlurStrength(5.f)
				/*SNew(SImage)
				.ColorAndOpacity(FColor::Transpancy)*/
			]
		
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)

				// Title Text
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(TitleText)
					.Justification(ETextJustify::Center)
				]
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(20.f, 0.f, 0.f, 0.f)
			[
				SNew(SHorizontalBox)

				//Play Button
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SWidgetMyClass::OnPlayClicked)
					.ButtonColorAndOpacity(FColor::Transparent)
					.ContentPadding(2.f)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.ColorAndOpacity(FColor::White)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
				]

				//Settings Button
				/*+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					//.OnClicked(this, &SWidgetMyClass::OnSettingClicked)
					.ButtonColorAndOpacity(FColor::Transparent)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.ColorAndOpacity(FColor::White)
						.Text(SettingsText)
						.Justification(ETextJustify::Center)
					]
				]*/

				//Quit Button
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SWidgetMyClass::OnQuitClicked)
					.ButtonColorAndOpacity(FColor::Transparent)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.ColorAndOpacity(FColor::White)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]

				]
		] 
	];
}


 
FReply SWidgetMyClass::OnPlayClicked() const // click on the play button remove menu from screen
{
	if (OwningHUD.IsValid())  //Basically saying if the blueprint is valid
	{
		OwningHUD->RemoveMenu();
	}
	
	return FReply::Handled();
}


FReply SWidgetMyClass::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}

	return FReply::Handled(); // if reply handled
}



