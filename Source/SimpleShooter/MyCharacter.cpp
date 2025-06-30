// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "TimerManager.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	gun=GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	gun->SetOwner(this);

	Health=MaxHealth;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMyCharacter::isDead() const
{
	return Health<=0;
}

float AMyCharacter::GetHealthPercentage() const
{
	return Health/MaxHealth;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::moveforward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Looksideways"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("Movesideways"), this, &AMyCharacter::movesideways);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&AMyCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AMyCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyCharacter::StartShooting);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &AMyCharacter::StopShooting);
	PlayerInputComponent->BindAction(TEXT("Crouch"),EInputEvent::IE_Pressed,this,&AMyCharacter::Crouch);


	// or we can directly bind the addmovementinput and addcontrollerpitchinput
	//  PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&APawn::AddMovementInput);
	//  PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&APawn::AddControllerPitchInput);
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	float DamageApplied=Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser); //run the parent function first before overriding the whole functionality
	DamageApplied= FMath::Min(DamageApplied,Health);

	if(DamageApplied>0)	Health-=DamageApplied;

	UE_LOG(LogTemp,Warning,TEXT("Health left: %f"),Health);

	if(isDead())
	{
		ASimpleShooterGameModeBase* GameMode=GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

		if(GameMode!=nullptr) GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();	
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
	}

	return DamageApplied;
}

void AMyCharacter::moveforward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AMyCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::movesideways(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AMyCharacter::LookUpRate(float value)
{
	AddControllerPitchInput(value*Rotation_Rate*GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookRightRate(float value)
{
	AddControllerYawInput(value*Rotation_Rate*GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::shoot()
{
	UE_LOG(LogTemp,Warning,TEXT("Shot"));
	gun->TriggerGun();
}

void AMyCharacter::StartShooting()
{
    if (!bIsShooting)
    {
        bIsShooting = true;
        shoot(); 
        GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &AMyCharacter::shoot, FireRate, true);
    }
}

void AMyCharacter::Crouch()
{
	if(state==false) state=true;
	else state=false;
}

void AMyCharacter::StopShooting()
{
    bIsShooting = false;
    GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}
