// Fill out your copyright notice in the Description page of Project Settings.


#include "SemiAutomaticWeapon.h"

void ASemiAutomaticWeapon::StartFire(APlayerCharacter *PlayerRef)
{
	if (!CanShoot)
	{
		return;
	}
	PlayerCharacter = PlayerRef;
	FireShot();
	CanShoot = false;
	GetWorldTimerManager().SetTimer(RateWeaponTimerHandle, this, &ASemiAutomaticWeapon::EnableCanShoot, 1.0f, false, TimeBetweenShot);
}

// Dont take out there is nothing to stop there but the function need to be overload
void ASemiAutomaticWeapon::StopFire()
{

}

void ASemiAutomaticWeapon::BeginPlay()
{
	Super::BeginPlay();
}
