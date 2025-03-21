// Fill out your copyright notice in the Description page of Project Settings.


#include "ISMController.h"

#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AISMController::AISMController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	SetRootComponent(InstancedStaticMeshComponent);
}

void AISMController::Initialise(UStaticMesh* mesh, UMaterialInterface* material)
{
	InstancedStaticMeshComponent->SetStaticMesh(mesh);
	InstancedStaticMeshComponent->SetMaterial(0, material);
}

// Called when the game starts or when spawned
void AISMController::BeginPlay()
{
	Super::BeginPlay();
	
}

