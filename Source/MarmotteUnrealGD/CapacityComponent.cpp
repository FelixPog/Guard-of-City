// Fill out your copyright notice in the Description page of Project Settings.


#include "CapacityComponent.h"


void UCapacityComponent::StartCooldown() 
{
	IsCapacityReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &UCapacityComponent::EnableCapacity, 1.0f, false, CapacityCooldown);
}

// Dont take out
bool UCapacityComponent::UseCapacity()
{
	UE_LOG(LogTemp, Error, TEXT("Dont use UseCapacity from the CapacityComponent"));
	return false;
}

void UCapacityComponent::EnableCapacity()
{
    IsCapacityReady = true;
    GetOwner()->GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
}


