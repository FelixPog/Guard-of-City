// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Enemy.h"
#include "Fortress.h"

void ASpawner::StartSpawner()
{
	CurrentWavesLeft = NumberOfWaves;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnWave, 1.0f, false, 0.0f);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	CurrentWavesLeft = NumberOfWaves;
}

void ASpawner::SpawnWave()
{
	UWorld* MyWorld = GetWorld();
	if (MyWorld == nullptr)
	{
		return;
	}

    FVector2D RandomPoint = FMath::RandPointInCircle(Radius);
    FVector SpawnLoc = GetActorLocation() + FVector(RandomPoint, 0);

	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for ( int ArraySize = 0; ArraySize < SpawnedActorsType.Num() ; ArraySize++)
	{
		for (int EnemySpawned = 0; EnemySpawned < NbOfEnemyByWave[ArraySize]; EnemySpawned++)
		{
			RandomPoint = FMath::RandPointInCircle(Radius);
			SpawnLoc = GetActorLocation() + FVector(RandomPoint, 0);
			MyWorld->SpawnActor<AEnemy>(SpawnedActorsType[ArraySize], SpawnLoc, FRotator::ZeroRotator, SpawnParams);
		}
	}

	CurrentWavesLeft--;

	if (CurrentWavesLeft <= 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnWave, 1.0f, false, TimeBetweenWave);
}

