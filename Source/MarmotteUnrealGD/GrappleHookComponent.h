// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapacityComponent.h"
#include "CableComponent.h"
#include "GrappleHookComponent.generated.h"

class APlayerCharacter;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHook);

UCLASS(Abstract, meta = (IsBlueprintBase = true))
class MARMOTTEUNREALGD_API UGrappleHookComponent : public UCapacityComponent
{
	GENERATED_BODY()
	UGrappleHookComponent();
	
public:
	virtual void BeginPlay() override;
	virtual bool UseCapacity() override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GrappleHookCapacity)
	UCableComponent* CableComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrappleHookCapacity)
	float CableWidth = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrappleHookCapacity)
	float GrappleHookDistance = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrappleHookCapacity)
	float TravelSpeed = 4000.0f;

        /*Timer before the player start going to the hook hit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrappleHookCapacity)
	float TimerDelay = 0.1f;

	/*Timer before the player start going to the hook hit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrappleHookCapacity)
	float PrelaunchStrengh = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GrappleHookCapacity)
	FVector HitLocation;
private:

	
	bool CheckForSurface();
	void PrepareLaunch();
	void LaunchPlayer();

	
	FTimerHandle PrelaunchTimerHandle;
};
