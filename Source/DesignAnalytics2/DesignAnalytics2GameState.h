// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DesignAnalytics2GameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, int, EnemyCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyKilled, int, EnemyCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewWave, int, WaveCount);

class AEnemySpawner;

UCLASS()
class DESIGNANALYTICS2_API ADesignAnalytics2GameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void EnemySpawned();

	UFUNCTION(BlueprintCallable)
	void EnemyKilled(int enemyType);

	UFUNCTION(BlueprintCallable)
	void NewWave();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> EnemiesDefeated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesDefeatedCounter = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaveNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesLeftThisWave = 0;

	UPROPERTY(BlueprintAssignable)
	FOnEnemySpawned OnEnemySpawnedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyKilled OnEnemyKilledDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnNewWave OnNewWaveDelegate;

	AEnemySpawner* EnemySpawner;
};
