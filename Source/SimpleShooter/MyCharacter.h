#pragma once
#include "Gun.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"
UCLASS()
class SIMPLESHOOTER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool isDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;
	
	void shoot();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
private:
	void moveforward(float value);
	void LookUp(float Value);
	void movesideways(float value);
	void LookUpRate(float value);
	void LookRightRate(float value);
	void StopShooting();
	void StartShooting();
	
	

	FTimerHandle ShootingTimer;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float FireRate =.1f;

	bool bIsShooting=false;

	UPROPERTY(EditAnywhere)
	float Rotation_Rate=50.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	class AGun* gun;


	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess = "true"))
	float MaxHealth=100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
