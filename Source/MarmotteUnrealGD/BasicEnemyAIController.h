// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicEnemyAIController.generated.h"

/**
 * 
 */
class UBehaviorTree;
UCLASS()
class MARMOTTEUNREALGD_API ABasicEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABasicEnemyAIController();
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = DwarfAI)
	class UBehaviorTree* BasicEnemyBehavior = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = DwarfAI)
	FName TargetTag = "AITarget";
	
private :
	FName TargetActorKey = "PlayerFortress";
};
