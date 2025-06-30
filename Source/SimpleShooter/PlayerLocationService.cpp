// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLocationService.h"
#include "Kismet/Gameplaystatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
void UPlayerLocationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn * Pawn= UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(Pawn==nullptr) return;

    if(OwnerComp.GetAIOwner()==nullptr) return;

    if(OwnerComp.GetAIOwner()->LineOfSightTo(Pawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),Pawn);
    }
    else OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

}

UPlayerLocationService::UPlayerLocationService()
{
    NodeName= "ActorLocation";
}
