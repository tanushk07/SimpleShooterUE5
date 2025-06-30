// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    Pawn= UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(BehaviorTree!=nullptr)
    {
        RunBehaviorTree(BehaviorTree);
    }

    // GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),Pawn->GetActorLocation());
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // if(LineOfSightTo(Pawn))
    // {
    //     MoveToActor(Pawn,300);
    //     SetFocus(Pawn);
    // }
    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }

    // if(LineOfSightTo(Pawn))
    // {
    //     // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),Pawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLoc"),Pawn->GetActorLocation());
    // }
    // else GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
}

bool AShooterAIController::isDead() const
{
    AMyCharacter * ControlledCharacter =Cast<AMyCharacter>(GetPawn());

    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->isDead();
    }
    return true;
}

