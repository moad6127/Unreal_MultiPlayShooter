// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Blaster/BlasterType/Team.h"
#include "Blaster/Weapon/WeaponTypes.h"
#include "BlasterPlayerState.generated.h"
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	/*
	*
	* Replication notifies
	*/
	virtual void OnRep_Score() override;

	UFUNCTION()
	virtual void OnRep_Defeat();

	UFUNCTION()
	virtual void OnRep_KillerName();

	UFUNCTION()
	virtual void OnRep_WeaponType();


	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
	void UpdateDeathMessage(FString Name);
	void UpdateWeaponTpye(EWeaponType Type);
private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* Controller;

	UPROPERTY(ReplicatedUsing = OnRep_Defeat)
	int32 Defeats;

	UPROPERTY(ReplicatedUsing = OnRep_KillerName)
	FString KillerName;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponType)
	EWeaponType WeaponType;

	FString WeaponTypeToString(EWeaponType Type);

	UPROPERTY(Replicated)
	ETeam Team = ETeam::ET_NoTeam;

public:
	FORCEINLINE ETeam GetTeam() const { return Team; }
	FORCEINLINE void SetTeam(ETeam TeamToSet) { Team = TeamToSet; }
};
