// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CapacityComponent.generated.h"


UCLASS(Abstract, ClassGroup=(Custom), meta=(IsBlueprintBase = false) )
class MARMOTTEUNREALGD_API UCapacityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void StartCooldown();

	virtual bool UseCapacity();
protected:
	bool IsCapacityReady = true;

	/* Time between capacity launch and next one (in seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	float CapacityCooldown = 5.0f;

	/* Capacity name use to display information for player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	FString CapacityName = "Capacity";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	USoundBase* CapacitySound;
	
private:
	void EnableCapacity();
	FTimerHandle CooldownTimerHandle;
	
};
