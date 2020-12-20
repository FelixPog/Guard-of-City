// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapacityComponent.h"
#include "Projectile.h"

#include "ProjectileLauncherCapacity.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API UProjectileLauncherCapacity : public UCapacityComponent
{
	GENERATED_BODY()


public:
        virtual void BeginPlay() override;

	
protected:
	virtual bool UseCapacity() override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int MaxMunitions = 12;

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	int MunitionsLeft = 0;

private:
	bool ShotProjectile();
	void PlayAnimation();
	void PlaySound();
};
