// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "Enemy.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy->GetCanAttack())
	{
		if (Enemy != nullptr)
		{
			Enemy->StartAttack();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy != nullptr)
	{
		Enemy->StopAttack();
	}

	return EBTNodeResult::Aborted;
}
