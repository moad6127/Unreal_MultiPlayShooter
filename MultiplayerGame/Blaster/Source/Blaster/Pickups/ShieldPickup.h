// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ShieldPickup.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AShieldPickup : public APickup
{
	GENERATED_BODY()

protected:
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OVerlappdComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFroSweep,
		const FHitResult& SweepResult
	);

private:

	UPROPERTY(EditAnywhere)
	float ShieldReplentishAmount = 100.f;

	UPROPERTY(EditAnywhere)
	float ShieldReplentishTime = 5.f;

	
};
