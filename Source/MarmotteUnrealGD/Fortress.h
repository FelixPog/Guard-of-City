// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Fortress.generated.h"


class UHPComponent;

UCLASS()
class MARMOTTEUNREALGD_API AFortress : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFortress();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = MonActor)
	UStaticMeshComponent* FortressMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonActor)
	UHPComponent* HPComponent = nullptr;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
        
};
