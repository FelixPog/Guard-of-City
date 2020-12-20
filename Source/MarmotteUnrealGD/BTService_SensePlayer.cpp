// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SensePlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

class UAIPerceptionComponent;

void UBTService_SensePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* MyController = OwnerComp.GetAIOwner();
	UAIPerceptionComponent* AIPerception = nullptr;

	if (MyController)
	{
		AIPerception = MyController->FindComponentByClass<UAIPerceptionComponent>();
	}

	if (AIPerception == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller does not have a perception component"));
		return;
	}

	TArray<AActor*> PerceivedActors;
	AIPerception->GetCurrentlyPerceivedActors(PerceivedSense, PerceivedActors);

 	if (PerceivedActors.Num() != 0)
	{
		AActor* PlayerActor = nullptr;

		for (AActor* PerceivedActor : PerceivedActors)
		{
			if (PerceivedActor->ActorHasTag("Player"))
			{
				PlayerActor = PerceivedActor;
				break;
			}
		}

		if (PlayerActor != nullptr)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerActor);
		}		
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	
}
