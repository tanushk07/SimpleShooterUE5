// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn * Pawn)
{
    Super::PawnKilled(Pawn);

    APlayerController * PlayerController = Cast<APlayerController>(Pawn->GetController());

    if(PlayerController!= nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController *Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->isDead()) return;
    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bplayerwon)
{
    for(AController* controller : TActorRange<AController>(GetWorld()))
    {
        bool bisWinner = controller->IsPlayerController() ==bplayerwon;
        controller->GameHasEnded(controller->GetPawn(),bisWinner); // getpawn focuses the camera to the person who killed the playercontrollerpawn
    }
}
