// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

// TODO Add a function to feed data to spawner for each round
// TODO Add a unique id to identify each spawner in map

UCLASS()
class MARMOTTEUNREALGD_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartSpawner();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Type of enemy who will spawn by wave
	 * Need to be in the same order than Nb Of Enemy By Wave */
	UPROPERTY(EditAnywhere, Category = MySpawnerEnemies)
	TArray<TSubclassOf<class AEnemy>> SpawnedActorsType;

	/* Number of enemy from each type who will spawn by wave
	 * Need to be in the same order than Spawned Actors Type */
	UPROPERTY(EditAnywhere, Category = MySpawnerEnemies)
	TArray<int> NbOfEnemyByWave;
	
	/* Enemy will spawn around the spawner with this radius */
	UPROPERTY(EditAnyWhere, Category = MySpawner, meta = (ClampMin = "0.001"))
    float Radius = 250.0f;

	/* Number of waves for the current round */
	UPROPERTY(EditAnyWhere, Category = MySpawner, meta = (ClampMin = "1"))
	int NumberOfWaves = 1;

	/* Time between each wave to spawn for this spawner*/
	UPROPERTY(EditAnyWhere, Category = MySpawner, meta = (ClampMin = "0.1"))
	float TimeBetweenWave = 3.0f;

private:
	void SpawnWave();
	
	int CurrentWavesLeft = 1;
	
	FTimerHandle SpawnTimerHandle;
};
