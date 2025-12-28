// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleShooterPlayerController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
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
    HUDWidget->RemoveFromParent();

    GetWorldTimerManager().SetTimer(timerhandle, this, &ASimpleShooterPlayerController::RestartGame, TimerDelay);
}

void ASimpleShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUD);
    if (HUDWidget != nullptr) {
        HUDWidget->AddToViewport();
    }
}

void ASimpleShooterPlayerController::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

