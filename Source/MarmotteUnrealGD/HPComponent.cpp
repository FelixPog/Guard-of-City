// Fill out your copyright notice in the Description page of Project Settings.


#include "HPComponent.h"

// Sets default values for this component's properties
UHPComponent::UHPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHPComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

/*
* True = IsDead
* False = IsAlive
*/
bool UHPComponent::TakeDamage(const float Damage)
{
	if (Damage <= 0.0f)
	{
		return false;
	}

	CurrentHP -= Damage;

	return CurrentHP <= 0.0f;
}

void UHPComponent::GetHealed(const float HPHealed)
{
	if (HPHealed <= 0.0f || CurrentHP == MaxHP)
	{
		return;
	}

	CurrentHP += HPHealed;

	if (CurrentHP >= MaxHP)
	{
		CurrentHP = MaxHP;
	}
}

void UHPComponent::AddMaxHP(const float HealthPoint)
{
	if (HealthPoint <= 0.0f)
	{
		return;
	}

	MaxHP += HealthPoint;
}


void UHPComponent::RemoveMaxHP(const float HealthPoint)
{
	if (MaxHP <= 1.0f || HealthPoint <= 0.0f)
	{
		return;
	}

	MaxHP -= HealthPoint;

	if (MaxHP < 1.0f)
	{
		MaxHP = 1.0f;
	}
}

float UHPComponent::GetHeathPercentage()
{
	if (MaxHP <= 0.0f)
	{
		return 0.0f;
	}
	
	return CurrentHP / MaxHP;
}
