// Fill out your copyright notice in the Description page of Project Settings.


#include "DesignAnalytics2GameState.h"
#include "Enemy/EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

void ADesignAnalytics2GameState::BeginPlay()
{
	Super::BeginPlay();

	EnemySpawner = Cast<AEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawner::StaticClass()));
}

void ADesignAnalytics2GameState::EnemySpawned()
{
	EnemiesLeftThisWave++;
	OnEnemySpawnedDelegate.Broadcast(EnemiesLeftThisWave);
	UE_LOG(LogTemp, Warning, TEXT("Enemy spawned, %d enemies left"), EnemiesLeftThisWave);
}

void ADesignAnalytics2GameState::EnemyKilled(int enemyType)
{
	EnemiesLeftThisWave--;
	EnemiesDefeatedCounter++;
	EnemiesDefeated.Add(enemyType);
	OnEnemyKilledDelegate.Broadcast(EnemiesLeftThisWave);
	UE_LOG(LogTemp, Warning, TEXT("Enemy killed, %d enemies left"), EnemiesLeftThisWave);

	// If spawner isn't spawning anymore enemies, and all enemies are killed, start the next wave.
	if(!EnemySpawner->IsSpawning && EnemiesLeftThisWave <= 0)
	{
		EnemySpawner->Spawn((WaveNumber + 1) * 3);
	}
}

void ADesignAnalytics2GameState::NewWave()
{
	WaveNumber++;
	OnNewWaveDelegate.Broadcast(WaveNumber);
	UE_LOG(LogTemp, Warning, TEXT("Wave %d started"), WaveNumber);
}
