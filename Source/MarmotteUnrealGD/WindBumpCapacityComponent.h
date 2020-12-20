// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapacityComponent.h"
#include "WindBumpCapacityComponent.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API UWindBumpCapacityComponent : public UCapacityComponent
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* SphereComponent;
	
public:
	virtual void BeginPlay() override;
	UWindBumpCapacityComponent();

	virtual bool UseCapacity() override;

	void BumpEnemy();
	void StopBump();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindBumpCapacity)
	float Radius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindBumpCapacity)
	float SpellDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindBumpCapacity)
	float TimeBetweenBump = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindBumpCapacity)
	float BumpStrength = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WindBumpCapacity)
	UParticleSystem* ParticleDuringSpell;

private:
	FTimerHandle MicroBumpTimerHandle;
	FTimerHandle StopBumpTimerHandle;
	float TimeLeft = 0.0f;
};
