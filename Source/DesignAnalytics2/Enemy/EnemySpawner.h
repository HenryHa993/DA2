// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DESIGNANALYTICS2_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FVector GetRandomLocationInRange();

	UFUNCTION(BlueprintCallable)
	void Spawn(int amount);

	UFUNCTION(BlueprintCallable)
	void SpawnOnce();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTiming;

	int SpawnCounter = 3;
	int CurrentSpawnCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyPawn> Enemy;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
};
