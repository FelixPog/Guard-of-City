// Fill out your copyright notice in the Description page of Project Settings.


#include "WindBumpCapacityComponent.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"

#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


UWindBumpCapacityComponent::UWindBumpCapacityComponent()
{
}

void UWindBumpCapacityComponent::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent = NewObject<USphereComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	 
	if (SphereComponent != nullptr)
	{
		SphereComponent->AttachToComponent(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->SetRelativeLocation(FVector::ZeroVector);
		SphereComponent->SetSphereRadius(Radius);
	}
	SphereComponent->RegisterComponent();
}



bool UWindBumpCapacityComponent::UseCapacity()
{
	if (!IsCapacityReady)
	{
		return false;
	}

	if (CapacitySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CapacitySound, GetOwner()->GetActorLocation());
	}
	StartCooldown();

	if (ParticleDuringSpell != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(ParticleDuringSpell, Cast<APlayerCharacter>(GetOwner())->GetCapsuleComponent(), NAME_None, FVector::ZeroVector,FRotator::ZeroRotator, FVector(1), EAttachLocation::SnapToTargetIncludingScale, true);
	}
	
	GetOwner()->GetWorldTimerManager().SetTimer(MicroBumpTimerHandle, this, &UWindBumpCapacityComponent::BumpEnemy, TimeBetweenBump, true, 0.0f);
	GetOwner()->GetWorldTimerManager().SetTimer(StopBumpTimerHandle, this, &UWindBumpCapacityComponent::StopBump, 1.0f, false, SpellDuration);

	return true;
}

void UWindBumpCapacityComponent::BumpEnemy()
{
	TArray<AActor*> EnemiesInRange;

	GetOwner()->GetOverlappingActors(EnemiesInRange);

	for (AActor* Enemy : EnemiesInRange)
	{
		if (Enemy->ActorHasTag("Enemy"))
		{
			FVector DirectionVector = Enemy->GetActorLocation() - GetOwner()->GetActorLocation() ;
			DirectionVector.Normalize();
			DirectionVector.Z = 0.0f;
			
			//TODO Add Impulse to the enemy inside sphere
			Cast<AEnemy>(Enemy)->GetController()->StopMovement();
			Cast<AEnemy>(Enemy)->GetCharacterMovement()->AddImpulse(DirectionVector * BumpStrength);
		}
	}
}

void UWindBumpCapacityComponent::StopBump()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(MicroBumpTimerHandle);
	GetOwner()->GetWorldTimerManager().ClearTimer(StopBumpTimerHandle);
}
