// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BasicEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MARMOTTEUNREALGD_API UBasicEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dwarf)
		bool IsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dwarf)
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dwarf)
		bool IsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dwarf)
	float WalkBlendRatio = 0.0f;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	
};
