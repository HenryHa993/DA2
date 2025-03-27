// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "DesignAnalytics2/DesignAnalytics2Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AEnemyProjectile::AEnemyProjectile() : ADesignAnalytics2Projectile()
{
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bShouldBounce = false;

	// Die after 2 seconds by default
	InitialLifeSpan = Lifetime;
}

void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if(OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		
		ADesignAnalytics2Character* player = Cast<ADesignAnalytics2Character>(OtherActor);
		if(player != nullptr)
		{
			player->HealthComponent->Damage(1);
		}
		Destroy();
	}
}

