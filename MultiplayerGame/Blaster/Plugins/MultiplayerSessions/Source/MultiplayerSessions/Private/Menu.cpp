// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/WidgetSwitcher.h"
#include "ServerRow.h"
#include "Components/TextBlock.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	PathToLobby = FString::Printf(TEXT("%s?listen"),*LobbyPath);
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSessoin);
		MultiplayerSessionSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &ThisClass::OnFindSession);
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionSubsystem->MultiplayerOnStartySessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}



bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	if (HostMenuHostButton)
	{
		HostMenuHostButton->OnClicked.AddDynamic(this, &ThisClass::HostMenuHostButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &ThisClass::CancelButtonClicked);
	}
	if (JoinMenuCancelButton)
	{
		JoinMenuCancelButton->OnClicked.AddDynamic(this, &ThisClass::CancelButtonClicked);
	}
	if (JoinMenuJoinButton)
	{
		JoinMenuJoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinMenuJoinButtonClicked);
	}

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSessoin(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("Session Created Successfully!"))
			);
		}

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLobby);

		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failed to create session!"))
			);
		}
		HostButton->SetIsEnabled(true);
	}
}

void UMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MultiplayerSessionSubsystem == nullptr)
	{
		return;
	}

	if (SelectedIndex.IsSet())
	{
		MultiplayerSessionSubsystem->JoinSession(SessionResults[SelectedIndex.GetValue()]);
	}
	else
	{
		uint32 i = 0;
		for (auto Result : SessionResults)
		{
			SetServerList(Result, i++);
		}
	}

	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		JoinMenuJoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinMenuJoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{
	if (SubMenuSystem == nullptr)
	{
		return;
	}
	if (HostMenu == nullptr)
	{
		return;
	}
	SubMenuSystem->SetActiveWidget(HostMenu);
}

void UMenu::JoinButtonClicked()
{
	if (SubMenuSystem == nullptr)
	{
		return;
	}
	if (JoinMenu == nullptr)
	{
		return;
	}
	SubMenuSystem->SetActiveWidget(JoinMenu);
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSession(10000);
	}
}

void UMenu::HostMenuHostButtonClicked()
{
	HostMenuHostButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::CancelButtonClicked()
{
	if (SubMenuSystem == nullptr)
	{
		return;
	}
	if (InitMenu == nullptr)
	{
		return;
	}
	SubMenuSystem->SetActiveWidget(InitMenu);
}


void UMenu::JoinMenuJoinButtonClicked()
{
	JoinMenuJoinButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSession(10000);
	}
}

void UMenu::SetServerList(FOnlineSessionSearchResult ServerNames, uint32 Index)
{
	UWorld* World = this->GetWorld();
	if (World == nullptr)
	{
		return;
	}
	
	
	UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
	if (Row == nullptr)
	{
		return;
	}
	FString SettingValue;
	ServerNames.Session.SessionSettings.Get(FName("MatchType"), SettingValue);

	Row->ServerName->SetText(FText::FromString(ServerNames.Session.OwningUserName));
	Row->MatchType->SetText(FText::FromString(SettingValue));

	Row->Setup(this, Index);
	ServerList->AddChild(Row);

}
void UMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}
void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
