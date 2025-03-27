// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyProjectile.h"
#include "DesignAnalytics2/Components/HealthComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class DESIGNANALYTICS2_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);*/

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(float newHealth);

	UFUNCTION(BlueprintCallable)
	void OnDamaged(float damage);

	// Animations
	UFUNCTION(BlueprintCallable)
	void ScaleAnimation();

	UFUNCTION(BlueprintCallable)
	void DeathAnimation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthScaleRatio = 0.3f;
	float CurrentScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float ScaleAnimationSpeed = 10.0f;;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> EnemyMaterials;

	bool Dead = false;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEnemyProjectile>> Projectiles;

	int EnemyType;
};
