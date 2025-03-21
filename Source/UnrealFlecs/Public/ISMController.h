// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISMController.generated.h"

UCLASS()
class UNREALFLECS_API AISMController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AISMController();

	void Initialise(UStaticMesh* mesh, UMaterialInterface* material);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent = nullptr;

private:
	TArray<FTransform> Transforms;
};
