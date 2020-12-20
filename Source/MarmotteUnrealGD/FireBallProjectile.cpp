// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBallProjectile.h"

void AFireBallProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DoAoeDamage();
	DestroyProjectile();
}

AFireBallProjectile::AFireBallProjectile()
{
	FireBallLight = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("PointLight")));
}
