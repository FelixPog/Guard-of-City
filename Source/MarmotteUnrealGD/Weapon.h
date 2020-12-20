// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class APlayerCharacter;
class UAnimMontage;
class USoundBase;
class USkeletalMeshComponent;
class USceneComponent;
class UDamageComponent;

UCLASS(meta = (IsBlueprintBase = false))
class MARMOTTEUNREALGD_API AWeapon : public AActor
{
	GENERATED_BODY()

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	

public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual void StartFire(APlayerCharacter* PlayerRef);
	virtual void StopFire();
	void StartReload();
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FireShot();
	virtual void EnableCanShoot();

	UPROPERTY(EditAnywhere, Category = Damage)
	UDamageComponent* DamageComponent = nullptr;
	
	/*
	 * How many bullets the gun can shoot by second
	 * Does not take reloading time in count
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun, meta=(ClampMin = "0.001"))
	float ShotPerSeconds = 10.0f;

	/* Number of munitions in one magazine */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun, meta = (ClampMin = "1"))
	int MaxMunitions = 30;

	/* Time for the player to reload the gun (in seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	float ReloadingTime = 1.0f;

	/* Bullets range */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	float WeaponRange = 20000.f;

	/* Particles display for each shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	UParticleSystem* MuzzleParticles;

	/* Particles display on target at impact */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	UParticleSystem* ImpactParticles;

	/*
	 * Munition left in gun
	 * Need to be protected for UI update
	 */
	UPROPERTY(BlueprintReadOnly, Category = HitscanGun)
	int MunitionsLeft = 0;
public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	USoundBase* FireSound;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	USoundBase* ReloadSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitscanGun)
	UAnimMontage* FireAnimation;

protected:
	float TimeBetweenShot = 1.0f;
	FTimerHandle RateWeaponTimerHandle;
	// Reference on Player Shooting
	APlayerCharacter* PlayerCharacter = nullptr;
	bool CanShoot = true;
private:

	// Reloading var
	bool IsReloading = false;
	FTimerHandle ReloadTimerHandle;	
	void Reload();

public:
	/** Returns FP_MuzzleLocation subobject **/
	FORCEINLINE class USceneComponent* GetFPMuzzleLocation() const { return FP_MuzzleLocation; }
};
