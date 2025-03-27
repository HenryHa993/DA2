// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"


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

	int randomNum = FMath::RandRange(1,3);
	HealthComponent->CurrentHealth = randomNum;
	HealthComponent->MaxHealth = randomNum;

	CurrentScale = HealthComponent->MaxHealth * HealthScaleRatio;
	StaticMeshComponent->SetWorldScale3D({0.01f, CurrentScale, CurrentScale});

	StaticMeshComponent->SetMaterial(0, EnemyMaterials[randomNum-1]);

	//CapsuleComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyPawn::OnOverlapBegin);

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

/*void AEnemyPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector velocity = -FloatingPawnMovement->Velocity;
	FloatingPawnMovement->Velocity = velocity;
	UE_LOG(LogTemp, Warning, TEXT("Overlap."));

}*/

void AEnemyPawn::DeathAnimation()
{
	if(Dead)
	{
		if(CurrentScale <= 0)
		{
			Destroy();
		}
		CurrentScale = FMath::Lerp(CurrentScale, 0, GetWorld()->DeltaTimeSeconds * ScaleAnimationSpeed);
		StaticMeshComponent->SetWorldScale3D({0.01f,CurrentScale,CurrentScale});
	}
}

void AEnemyPawn::OnDeath()
{
	Dead = true;
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
	if(!(CurrentScale - targetScale <= 0.1f))
	{
		CurrentScale = FMath::Lerp(CurrentScale, targetScale, GetWorld()->DeltaTimeSeconds * ScaleAnimationSpeed);
		StaticMeshComponent->SetWorldScale3D({0.01f,CurrentScale,CurrentScale});
	}
}

