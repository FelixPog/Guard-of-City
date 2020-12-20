// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UDamageComponent;
UCLASS()
class MARMOTTEUNREALGD_API AProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

protected:
	UPROPERTY(EditAnywhere, Category = Damage)
	UDamageComponent* DamageComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	USoundBase* ProjectileDestroySound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	UParticleSystem* DestroyedParticle;
	

	/*
	 * Time before the projectile get destroyed (in seconds)
	 * Except if other condition destroyed it first
	 * Cant be infinity to avoid performance issues
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta=(ClampMin="0.001"))
	float LifeSpan = 5.0f;

	virtual void BeginPlay() override;

	virtual void DestroyProjectile();
public:	
	AProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	
};
