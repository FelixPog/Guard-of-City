// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBallCapacityComponent.h"

#include "FireBallProjectile.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UFireBallCapacityComponent::UseCapacity()
{
	if (!IsCapacityReady) 
	{
		return false;
	}

	//try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		APlayerCharacter* PlayerCharacter = static_cast<APlayerCharacter *>(UGameplayStatics::GetPlayerPawn(World, 0));
		if (World != nullptr)
		{
			const FRotator SpawnRotation = PlayerCharacter->GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((PlayerCharacter != nullptr) ? PlayerCharacter->GetFPMuzzleLocation()->GetComponentLocation() : PlayerCharacter->GetActorLocation()) + SpawnRotation.RotateVector(PlayerCharacter->GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// spawn the projectile at the muzzle
			World->SpawnActor<AFireBallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			if (CapacitySound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CapacitySound, GetOwner()->GetActorLocation());
			}
			
			StartCooldown();
			return true;
		}
	}

	return false;
}
