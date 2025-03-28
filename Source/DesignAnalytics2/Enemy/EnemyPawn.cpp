// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "EnemyAIController.h"
#include "EnemyProjectile.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "DesignAnalytics2/DesignAnalytics2GameState.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//RootComponent = SceneComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	//StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->CastShadow = false;
	RootComponent = StaticMeshComponent;
	/*CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = CapsuleComponent;*/

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	// todo: Set up default parameters for how I want the cubes to move.
	FloatingPawnMovement->Deceleration = 200;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	bUseControllerRotationRoll = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	HealthComponent->OnDeathDelegate.AddUniqueDynamic(this, &AEnemyPawn::AEnemyPawn::OnDeath);
	HealthComponent->OnHealthChangedDelegate.AddUniqueDynamic(this, &AEnemyPawn::AEnemyPawn::OnHealthChanged);
	HealthComponent->OnDamagedDelegate.AddUniqueDynamic(this, &AEnemyPawn::AEnemyPawn::OnDamaged);

	EnemyType = FMath::RandRange(1,3);
	HealthComponent->CurrentHealth = EnemyType;
	HealthComponent->MaxHealth = EnemyType;

	// Set to zero so scales to size in spawning
	CurrentScale = 0;
	StaticMeshComponent->SetWorldScale3D({0.01f, 0, 0});

	StaticMeshComponent->SetMaterial(0, EnemyMaterials[EnemyType-1]);
	Projectile = Projectiles[EnemyType-1];

	GameState = Cast<ADesignAnalytics2GameState>(GetWorld()->GetGameState());
	GameState->EnemySpawned();

	Super::BeginPlay();
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	ScaleAnimation();
	DeathAnimation();
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyPawn::Fire()
{
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector playerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator spawnRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerLocation);
	FVector spawnLocation = GetActorLocation() + spawnRotation.Vector() * 100.0f;
	
	// Spawn the projectile at the muzzle
	GetWorld()->SpawnActor<AEnemyProjectile>(Projectile->GetDefaultObject()->GetClass(), spawnLocation, spawnRotation, ActorSpawnParams);
}

void AEnemyPawn::DeathAnimation()
{
	if(Dead)
	{
		if(CurrentScale <= 0)
		{
			if(FMath::RandRange(1,10) <= 2)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				GetWorld()->SpawnActor<AActor>(HealthDrop->GetDefaultObject()->GetClass(), GetActorLocation() + FVector(0,0,-200), FRotator::ZeroRotator, ActorSpawnParams);
			}
			Destroy();
		}
		AEnemyAIController* controller = Cast<AEnemyAIController>(GetController());
		if(controller != nullptr)
		{
			controller->GetBrainComponent()->StopLogic(TEXT("Death"));
			controller->UnPossess();
		}

		CurrentScale = FMath::Lerp(CurrentScale, 0, GetWorld()->DeltaTimeSeconds * ScaleAnimationSpeed);
		StaticMeshComponent->SetWorldScale3D({0.01f,CurrentScale,CurrentScale});
	}
}

void AEnemyPawn::OnDeath()
{
	if(Dead)
	{
		return;
	}
	Dead = true;
	GameState->EnemyKilled(EnemyType);
}

void AEnemyPawn::OnHealthChanged(float newHealth)
{
	
}

void AEnemyPawn::OnDamaged(float damage)
{
	// todo: knockback
	
}

void AEnemyPawn::ScaleAnimation()
{
	float currentHealth = HealthComponent->CurrentHealth;
	float targetScale = currentHealth * HealthScaleRatio;
	if(!(CurrentScale - targetScale <= 0.1f) || !(CurrentScale - targetScale >= -0.1f))
	{
		CurrentScale = FMath::Lerp(CurrentScale, targetScale, GetWorld()->DeltaTimeSeconds * ScaleAnimationSpeed);
		StaticMeshComponent->SetWorldScale3D({0.01f,CurrentScale,CurrentScale});
	}
}

