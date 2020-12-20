// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncherCapacity.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UProjectileLauncherCapacity::BeginPlay()
{
	Super::BeginPlay();

	MunitionsLeft = MaxMunitions;
}

bool UProjectileLauncherCapacity::UseCapacity()
{
	if (!IsCapacityReady)
	{
		return false;
	}

	if (MunitionsLeft <= 0)
	{
		MunitionsLeft = MaxMunitions;
		StartCooldown();
		return true;
	}

	if (ShotProjectile())
	{
		PlaySound();
		PlayAnimation();
		StartCooldown();
		return true;
	}

	return false;
}

bool UProjectileLauncherCapacity::ShotProjectile()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter != nullptr && ProjectileClass != nullptr)
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
			return true;
		}
	}
	return false;
}

void UProjectileLauncherCapacity::PlayAnimation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter != nullptr && FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = PlayerCharacter->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UProjectileLauncherCapacity::PlaySound()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter != nullptr && FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, PlayerCharacter->GetActorLocation());
	}
}

