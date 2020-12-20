// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARMOTTEUNREALGD_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

	UFUNCTION()
	const float GetDamage() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Damage done by the bullet/weapon/character depending where the component is used */
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (ClampMin = "0.001"))
	float Damage = 1.0f;		
};
