// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AutomaticWeapon.generated.h"

/**
 * 
 */
UCLASS(meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API AAutomaticWeapon : public AWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire(APlayerCharacter * PlayerRef) override;

    virtual void StopFire() override;
	
protected:
	virtual void BeginPlay() override;
};