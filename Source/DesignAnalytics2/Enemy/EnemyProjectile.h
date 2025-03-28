// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesignAnalytics2/DesignAnalytics2Projectile.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class DESIGNANALYTICS2_API AEnemyProjectile : public ADesignAnalytics2Projectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyProjectile();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	UPROPERTY(EditAnywhere)
	float Damage = 1;

	UPROPERTY(EditAnywhere)
	float Speed = 900;

	UPROPERTY(EditAnywhere)
	float Lifetime = 2.0f;
};
