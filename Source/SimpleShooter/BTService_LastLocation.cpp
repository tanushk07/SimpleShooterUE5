// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastLocation.h"
#include "Kismet/Gameplaystatics.h"
#include "BehaviorTree/BlackboardComponent.h"



void UBTService_LastLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn * Pawn= UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(Pawn==nullptr) return;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),Pawn->GetActorLocation());
}

UBTService_LastLocation::UBTService_LastLocation()
{
    NodeName="LastLocationService";
}
