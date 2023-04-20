// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4 , FString TypeOfMatch = FString(TEXT("FreeForAll")),FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));

	void SetServerList(FOnlineSessionSearchResult ServerNames,uint32 Index);

	void SelectIndex(uint32 Index);

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// Callback for the custom delegate on the MultiplayerSessionSubsystem
	//
	UFUNCTION()
	void OnCreateSessoin(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	 
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SubMenuSystem;

	UPROPERTY(meta = (BindWidget))
	UButton* HostMenuHostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuJoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* InitMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;


	TOptional<uint32> SelectedIndex;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void HostMenuHostButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();

	UFUNCTION()
	void JoinMenuJoinButtonClicked();



	void MenuTearDown();
	//The Subsystem disinged to handle all online session functoinality
	class UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 NumPublicConnections{4};

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString MatchType{TEXT("FreeForAll")};


	FString PathToLobby{ TEXT("") };


};
