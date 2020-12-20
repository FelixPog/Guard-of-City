// Fill out your copyright notice in the Description page of Project Settings.


#include "FireProjectileComponent.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UFireProjectileComponent::UFireProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UFireProjectileComponent::StartFire(APlayerCharacter *PlayerRef)
{
	if (!CanFire) 
	{
		return;
	}
	PlayerCharacter = PlayerRef;

	GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &UFireProjectileComponent::ShotProjectile, TimeBetweenShot, true);
}


void UFireProjectileComponent::StopFire()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	CanFire = false;
	GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &UFireProjectileComponent::EnableCanFire, 1.0f, false, TimeBetweenShot);
}

// Called when the game starts
void UFireProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	MunitionsLeft = MaxMunitions;
	
}


void UFireProjectileComponent::ShotProjectile()
{
        // Check if Fire is still on CD
	if (!CanFire || MunitionsLeft <= 0)
	{
		return;
	}

	//try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = PlayerCharacter->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((PlayerCharacter->GetFPMuzzleLocation() != nullptr) ? PlayerCharacter->GetFPMuzzleLocation()->GetComponentLocation() : PlayerCharacter->GetActorLocation()) + SpawnRotation.RotateVector(PlayerCharacter->GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// spawn the projectile at the muzzle
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			MunitionsLeft--;
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, PlayerCharacter->GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = PlayerCharacter->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

        
}

void UFireProjectileComponent::EnableCanFire()
{
	CanFire = true;
	GetOwner()->GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}

