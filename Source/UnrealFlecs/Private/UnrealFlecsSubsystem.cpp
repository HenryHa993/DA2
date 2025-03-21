// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFlecsSubsystem.h"

void UUnrealFlecsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	World = new flecs::world;
	Super::Initialize(Collection);
}

void UUnrealFlecsSubsystem::Deinitialize()
{
	if(World) delete World;
	Super::Deinitialize();
}

flecs::world* UUnrealFlecsSubsystem::GetEcsWorld()
{
	return World;
}
