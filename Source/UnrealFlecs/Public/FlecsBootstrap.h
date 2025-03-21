// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "flecs.h"
#include "FlecsModuleBase.h"
#include "FlecsBootstrap.generated.h"

UCLASS()
class UNREALFLECS_API AFlecsBootstrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlecsBootstrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Bootstrap(flecs::world& ecs);

public:
	UPROPERTY(EditAnywhere, Category="FLECS")
	TArray<TSubclassOf<UFlecsModuleBase>> FlecsModules;
};
