// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoostCapacity.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void USpeedBoostCapacity::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter != nullptr)
	{
		InitialSpeed = PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}

	if (CapacityCooldown < BoostDuration)
	{
		BoostDuration = CapacityCooldown;
	}

}

bool USpeedBoostCapacity::UseCapacity()
{
	if (!IsCapacityReady)
	{
		return false;
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	
	if (PlayerCharacter == nullptr || PlayerCharacter->GetCharacterMovement() == nullptr)
	{
		return false;
	}

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed *= SpeedMultiplier;

	if (CapacitySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CapacitySound, GetOwner()->GetActorLocation());
	}
	
	StartCooldown();
	GetOwner()->GetWorldTimerManager().SetTimer(SpeedBoostTimerHandle, this, &USpeedBoostCapacity::ResetToInitialSpeed, 1.0f, false, BoostDuration);

	return true;
}

void USpeedBoostCapacity::ResetToInitialSpeed()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter != nullptr || PlayerCharacter->GetCharacterMovement() != nullptr)
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = InitialSpeed;
	}
}
