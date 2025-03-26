// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	// todo: Set up default parameters for how I want the cubes to move.
	FloatingPawnMovement->Deceleration = 0;
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	//GetMovementComponent()->Velocity = FVector(100,100,100);

	Super::BeginPlay();
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

