// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SHOOT.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_SHOOT : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTTask_SHOOT();
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
