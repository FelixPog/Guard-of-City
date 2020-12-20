// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AOEProjectile.h"
#include "Components/PointLightComponent.h"
#include "FireBallProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MARMOTTEUNREALGD_API AFireBallProjectile : public AAOEProjectile
{
	GENERATED_BODY()

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	AFireBallProjectile();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FireBall)
	UPointLightComponent* FireBallLight;
};
