// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocekt = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	UWorld* World = GetWorld();
	if (MuzzleFlashSocekt && World)
	{
		FTransform SocketTransform = MuzzleFlashSocekt->GetSocketTransform(GetWeaponMesh());
		// From muzzle flash socket to hit location from TraceUnderCrosshairs
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = InstigatorPawn;
		
		AProjectile* SpawnProjectile = nullptr;
		if (bUseServerSideRewind)
		{
			if (InstigatorPawn->HasAuthority()) //server
			{
				if (InstigatorPawn->IsLocallyControlled()) //server, host - use replicated projectile
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ProjectileClass,SocketTransform.GetLocation(),TargetRotation,SpawnParams);
					SpawnProjectile->bUseServerSideRewind = false;
					SpawnProjectile->Damage = Damage;
					SpawnProjectile->HeadShotDamage = HeadShotDamage;
				}
				else // server, not locallyconrolled - spawn non-replicated projectile, SSR
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
					SpawnProjectile->bUseServerSideRewind = true;
				}
			}
			else // client, using SSR
			{
				if (InstigatorPawn->IsLocallyControlled()) //clinet locallycontrolled - spawn non-replicated projectile, use SSR
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
					SpawnProjectile->bUseServerSideRewind = true;
					SpawnProjectile->TraceStart = SocketTransform.GetLocation();
					SpawnProjectile->InitialVelocity = SpawnProjectile->GetActorForwardVector() * SpawnProjectile->InitialSpeed;
				}
				else //client not locallyconrolled - spawn non-replicated projectile, no SSr
				{
					SpawnProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
					SpawnProjectile->bUseServerSideRewind = false;
				}
			}
		}
		else //Weapon not useing SSR
		{
			if (InstigatorPawn->HasAuthority())
			{
				SpawnProjectile = World->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
				SpawnProjectile->bUseServerSideRewind = false;
				SpawnProjectile->Damage = Damage;
				SpawnProjectile->HeadShotDamage = HeadShotDamage;

			}
		}
	}

}
