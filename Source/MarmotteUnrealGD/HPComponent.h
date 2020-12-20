// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARMOTTEUNREALGD_API UHPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHPComponent();

	/* Max health points of the Actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHP = 100.0f;

	/*
	 * True = IsDead
	 * False = IsAlive
	 */
	UFUNCTION()
	bool TakeDamage(const float Damage);

	UFUNCTION()
	void GetHealed(const float HPHealed);

	UFUNCTION()
	void AddMaxHP(const float HealthPoint);

	UFUNCTION()
	void RemoveMaxHP(const float HealthPoint);

	UFUNCTION(BlueprintCallable)
	float GetHeathPercentage();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Need to be protected to update UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHP = 0.0f;
};
