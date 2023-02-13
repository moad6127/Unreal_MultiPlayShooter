// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void MenuSetup();

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButtom;
	 
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButtom;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	//The Subsystem disinged to handle all online session functoinality
	class UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;
};
