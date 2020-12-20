// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapacityComponent.h"
#include "SpeedBoostCapacity.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API USpeedBoostCapacity : public UCapacityComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual bool UseCapacity() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementSpeedBuff)
	float SpeedMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementSpeedBuff)
	float BoostDuration = 1.5f;
	
private:

	void ResetToInitialSpeed();
	
	float InitialSpeed = 0.0f;
	FTimerHandle SpeedBoostTimerHandle;
};
