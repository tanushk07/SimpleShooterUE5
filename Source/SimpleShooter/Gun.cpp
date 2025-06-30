#include "Gun.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h" 
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(root);
	StaticMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

}
//hello

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::TriggerGun()
{
	UGameplayStatics::SpawnEmitterAttached(Fireeffect, StaticMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, StaticMesh, TEXT("MuzzleFlashSocket"));

	FHitResult BulletOutHit;
	FVector ShotFrom;

	bool success=GunTrace(BulletOutHit,ShotFrom);
	if (success)
	{
		// DrawDebugPoint(GetWorld(), BulletOutHit.Location, 10.f, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitEffect,BulletOutHit.Location,ShotFrom.Rotation(),true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),HitSound,BulletOutHit.Location);

		AActor* Hitactor = BulletOutHit.GetActor();

		if(Hitactor!=nullptr)
		{
	 		FPointDamageEvent DamageEvent(damage, BulletOutHit, ShotFrom, nullptr);
			AController *OwnerController= GetOwnerController();
			Hitactor->TakeDamage(damage,DamageEvent, OwnerController,this);
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
}

bool AGun::GunTrace(FHitResult &BulletOutHit,FVector &ShotFrom)
{
	FVector OutLocation;
	FRotator OutRotation;
	AController *OwnerController= GetOwnerController();
	if(OwnerController==nullptr) return false;

	OwnerController->GetPlayerViewPoint(OutLocation, OutRotation);
	ShotFrom = OutLocation;
	FVector LineEnd = OutLocation + OutRotation.Vector() * MaxDistance;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(BulletOutHit, OutLocation, LineEnd, ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}
