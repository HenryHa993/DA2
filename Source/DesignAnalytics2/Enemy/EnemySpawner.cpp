// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	//Spawn(10);
	GameState = Cast<ADesignAnalytics2GameState>(GetWorld()->GetGameState());
}

FVector AEnemySpawner::GetRandomLocationInRange()
{
	float xy = FMath::RandRange(-HorizontalRange, HorizontalRange);
	float z = FMath::RandRange(-VerticalRange, VerticalRange);
	return GetActorLocation() + FVector(xy, xy, z);
}

void AEnemySpawner::Spawn(int amount)
{
	SpawnCounter = amount;
	CurrentSpawnCounter = 0;
	IsSpawning = true;
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AEnemySpawner::SpawnOnce,
		SpawnTiming/amount,
		true,
		1.0f
		);

	GameState->NewWave();
}

void AEnemySpawner::SpawnOnce()
{
	if(CurrentSpawnCounter >= SpawnCounter)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy?"));
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		IsSpawning = false;
		// If we fail to spawn the last guy
		if(GameState->EnemiesLeftThisWave <= 0)
		{
			Spawn((GameState->WaveNumber + 1) * 3);
		}
		return;
	}
	CurrentSpawnCounter++;
	FVector spawnLocation = GetRandomLocationInRange();
	GetWorld()->SpawnActor<AEnemyPawn>(Enemy, spawnLocation, FRotator::ZeroRotator);
	//UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy Number %d"), CurrentSpawnCounter);

}

