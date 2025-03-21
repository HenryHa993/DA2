// Fill out your copyright notice in the Description page of Project Settings.


#include "FlecsBootstrap.h"

#include "UnrealFlecsSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFlecsBootstrap::AFlecsBootstrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFlecsBootstrap::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UUnrealFlecsSubsystem* flecsSubsystem = gameInstance->GetSubsystem<UUnrealFlecsSubsystem>();
	Bootstrap(*flecsSubsystem->GetEcsWorld());
	Super::BeginPlay();
}

void AFlecsBootstrap::Bootstrap(flecs::world& ecs)
{
	for(auto moduleType : FlecsModules)
	{
		auto module = NewObject<UFlecsModuleBase>(this, moduleType);
		module->Initialise(ecs);
	}
}
