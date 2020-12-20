// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapacityComponent.h"
#include "FireBallProjectile.h"

#include "FireBallCapacityComponent.generated.h"

UCLASS(Abstract, meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API UFireBallCapacityComponent : public UCapacityComponent
{
	GENERATED_BODY()
public:
         virtual bool UseCapacity() override;
protected:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = FireBall)
	TSubclassOf<AFireBallProjectile> ProjectileClass;

	
};
