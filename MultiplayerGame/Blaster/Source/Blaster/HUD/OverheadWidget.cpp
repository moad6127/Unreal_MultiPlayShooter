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
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	switch (RemoteRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_None:
		Role = FString("None");
		break;
	}
	APlayerState* PlayerState = InPawn->GetPlayerState();
	FString RemoteRoleString = FString::Printf(TEXT("Remote Role : %s "), *Role);

	SetDisplayText(RemoteRoleString);
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
