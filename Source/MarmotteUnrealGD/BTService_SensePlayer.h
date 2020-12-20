// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SensePlayer.generated.h"
/**
 * 
 */
class UAISense;
UCLASS()
class MARMOTTEUNREALGD_API UBTService_SensePlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = SenseService)
	TSubclassOf<UAISense> PerceivedSense;
	
protected:
	
	
};
