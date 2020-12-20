// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include  "Perception/AIPerceptionComponent.h"

ABasicEnemyAIController::ABasicEnemyAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));
}

void ABasicEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	const bool Success = RunBehaviorTree(BasicEnemyBehavior);
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Behavior tree could not run"));
		return;
	}

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, ActorsWithTag);

	if (ActorsWithTag.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI target is not tag in this map, please tag an AI target "));
		return;
	}

	AActor* AITarget = ActorsWithTag[0];
	if (AITarget != nullptr)
	{
		GetBlackboardComponent()->SetValueAsObject(TargetActorKey, reinterpret_cast<AActor*>(AITarget));
	}
	
	
}
