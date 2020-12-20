// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Projectile.h"
#include "Components/ActorComponent.h"
#include "FireProjectileComponent.generated.h"


class APlayerCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARMOTTEUNREALGD_API UFireProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireProjectileComponent();

	void StartFire(APlayerCharacter* PlayerRef);
	void StopFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	float ShotPerSeconds = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int MaxMunitions = 12;

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	int MunitionsLeft = 0;

private:
	void ShotProjectile();
	void EnableCanFire();

	float TimeBetweenShot = 1.0f;
	bool CanFire = true;
	APlayerCharacter* PlayerCharacter= nullptr;
	FTimerHandle ReloadTimerHandle;
};
