// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SHOOT.h"
#include "MyCharacter.h"
#include "AIController.h"
#include "Kismet/Gameplaystatics.h"


UBTTask_SHOOT::UBTTask_SHOOT()
{
    NodeName="Shoot";
}

EBTNodeResult::Type UBTTask_SHOOT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super:: ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr) return EBTNodeResult::Type::Failed;

    AMyCharacter* Pawn=Cast<AMyCharacter>(AIController->GetPawn());

    AMyCharacter* PlayerPawn=Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));


    if(Pawn==nullptr || PlayerPawn==nullptr || PlayerPawn->isDead()) return EBTNodeResult::Type::Failed;
    Pawn->shoot();
    return EBTNodeResult::Type::Succeeded;
}
