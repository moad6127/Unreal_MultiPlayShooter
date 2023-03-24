// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldPickup.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/BlasterComponents/BuffComponent.h"

void AShieldPickup::OnSphereOverlap(UPrimitiveComponent* OVerlappdComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OVerlappdComponent, OtherActor, OtherComp, OtherBodyIndex, bFroSweep, SweepResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		UBuffComponent* Buff = BlasterCharacter->GetBuff();
		if (Buff)
		{
			Buff->ReplenishShield(ShieldReplentishAmount, ShieldReplentishTime);
		}
	}
	Destroy();
}

