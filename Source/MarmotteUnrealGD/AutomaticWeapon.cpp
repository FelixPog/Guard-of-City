// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticWeapon.h"

void AAutomaticWeapon::StartFire(APlayerCharacter * PlayerRef)
{
    if (!CanShoot) 
	{
		return;
    }
	PlayerCharacter = PlayerRef;
	FireShot();

	GetWorldTimerManager().SetTimer(RateWeaponTimerHandle, this, &AAutomaticWeapon::FireShot, TimeBetweenShot, true);
}

void AAutomaticWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(RateWeaponTimerHandle);
}

void AAutomaticWeapon::BeginPlay()
{
	Super::BeginPlay();
}
