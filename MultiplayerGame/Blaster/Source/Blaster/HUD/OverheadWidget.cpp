// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{

	APlayerState* PlayerState = InPawn->GetPlayerState();
	FString PlayerName = FString();
	if (PlayerState)
	{
		PlayerName = PlayerState->GetPlayerName();
	}


	SetDisplayText(PlayerName);
}

void UOverheadWidget::SetPlayerName(FString Name)
{
	SetDisplayText(Name);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
