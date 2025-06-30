#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	AGun();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void TriggerGun();

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent *root;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent *StaticMesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem *Fireeffect;

	UPROPERTY(EditAnywhere)
	UParticleSystem *HitEffect;

	UPROPERTY(EditAnywhere)
	float damage = 10.f;

	bool GunTrace(FHitResult &BulletOutHit, FVector &ShotFrom);

	AController *GetOwnerController() const;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

public:
	UPROPERTY(EditAnywhere)
	float MaxDistance = 2000.f;
};
