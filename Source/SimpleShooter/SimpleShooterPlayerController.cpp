// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleShooterPlayerController.h"
#include "TimerManager.h"

#include "Blueprint/UserWidget.h"
void ASimpleShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(bIsWinner)
    {
        UUserWidget* WinScreenWidget= CreateWidget(this,GameWinWidget);
        
        if(WinScreenWidget != nullptr)
        {
            WinScreenWidget->AddToViewport();
        }
    }

    else
    {
        UUserWidget* LostScreenWidget= CreateWidget(this,GameLostWidget);

        if(LostScreenWidget != nullptr)
        {
            LostScreenWidget->AddToViewport();
        }
    }
    HUDWidget->RemoveFromViewport();

    GetWorldTimerManager().SetTimer(timerhandle, this, &APlayerController::RestartLevel, TimerDelay);
}

void ASimpleShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDWidget= CreateWidget(this,HUD);
    if(HUDWidget != nullptr) HUDWidget->AddToViewport();

}
