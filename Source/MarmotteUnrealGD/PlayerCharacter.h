// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "FireBallCapacityComponent.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AProjectile;
class AProjectileLauncher;
class UHPComponent;
class UInputComponent;
class UParticleSystem;
class UFireProjectileComponent;
class UCapacityComponent;

UCLASS()
class MARMOTTEUNREALGD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	UHPComponent* HPComponent = nullptr;

        // Capacity Slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capacity, meta = (AllowPrivateAccess = "true"))
	UCapacityComponent* FirstCapacityComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capacity, meta = (AllowPrivateAccess = "true"))
	UCapacityComponent* SecondCapacityComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capacity, meta = (AllowPrivateAccess = "true"))
	UCapacityComponent* ThirdCapacityComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capacity, meta = (AllowPrivateAccess = "true"))
	UCapacityComponent* FourthCapacityComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capacity, meta = (AllowPrivateAccess = "true"))
	UCapacityComponent* FifthCapacityComponent = nullptr;

	

public:

	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
        FVector GunOffset;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Primary weapon 
	void StartFire();
	void StopFire();
	void Reload();

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles stafing movement, left and right */
	void MoveRight(float Value);

	void UseFirstCapacity();
	void UseSecondCapacity();
	void UseThirdCapacity();
	void UseFourthCapacity();
	void UseFifthCapacity();

        //TODO Feature Take Out because no time 
	    //void AccessShop();

        // Weapon main

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PrimaryWeapon)
	TSubclassOf<AWeapon> PrimaryWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = PrimaryWeapon)
	AWeapon* PrimaryWeapon = nullptr;

        // Capacity class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	TSubclassOf<UCapacityComponent> FirstCapacityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	TSubclassOf<UCapacityComponent> SecondCapacityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	TSubclassOf<UCapacityComponent> ThirdCapacityClass;
	  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	TSubclassOf<UCapacityComponent> FourthCapacityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capacity)
	TSubclassOf<UCapacityComponent> FifthCapacityClass;

	UFUNCTION(BlueprintImplementableEvent, Category = Capacity)
	void OnFirstCapacityUse();

	UFUNCTION(BlueprintImplementableEvent, Category = Capacity)
	void OnSecondCapacityUse();

	UFUNCTION(BlueprintImplementableEvent, Category = Capacity)
	void OnThirdCapacityUse();

	UFUNCTION(BlueprintImplementableEvent, Category = Capacity)
	void OnFourthCapacityUse();

	UFUNCTION(BlueprintImplementableEvent, Category = Capacity)
	void OnFifthCapacityUse();
	
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Enemy)
	void OnDeath();
	
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns FP_MuzzleLocation subobject **/
	FORCEINLINE class USceneComponent* GetFPMuzzleLocation() const { return PrimaryWeapon->GetFPMuzzleLocation(); }
      
};
