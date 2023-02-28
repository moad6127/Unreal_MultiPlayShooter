// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


// Sets default values
ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasnigMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);

	bCanSound = true;
	ShellEjctionImpulse = 5.f;
	DestroyTime = 0.5f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();

	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	
	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjctionImpulse);
}

void ACasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (ShellSound && bCanSound)
	{
		bCanSound = false;
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	GetWorldTimerManager().SetTimer(
		ShellDestroyTimer,
		this,
		&ACasing::ShellDestroy,
		DestroyTime
	);
}

void ACasing::ShellDestroy()
{
	Destroy();
}





