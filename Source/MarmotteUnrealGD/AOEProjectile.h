// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "AOEProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MARMOTTEUNREALGD_API AAOEProjectile : public AProjectile
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float DamageRadius = 200.0f;
	
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void DoAoeDamage();
private:
};
