// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimpleShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UPROPERTY(EditAnywhere)
	float TimerDelay= 5.f;

	FTimerHandle timerhandle;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameLostWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameWinWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUD;

	class UUserWidget* HUDWidget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RestartGame();
};
