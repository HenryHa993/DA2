// Fill out your copyright notice in the Description page of Project Settings.


#include "InitsModule.h"

#include "ComponentsModule.h"

void UInitsModule::Initialise(flecs::world& ecs)
{
	ecs.entity().set<TestComponent>({1});
	
}

int32 UInitsModule::CreateISMController(UWorld* InWorld, UStaticMesh* InMesh, UMaterialInterface* InMaterial,
                                        ISM_Map& InMap)
{
	auto hash = HashCombine(GetTypeHash(InMaterial), GetTypeHash(InMesh));

	auto find = InMap.ISMs.Find(hash);

	if(find == nullptr)
	{
		FVector location = FVector::ZeroVector;
		FRotator rotation = FRotator::ZeroRotator;
		FActorSpawnParameters spawnInfo;

		auto controller = Cast<AISMController>(InWorld->SpawnActor(AISMController::StaticClass(), &location, &rotation, spawnInfo));
		controller->Initialise(InMesh, InMaterial);

		InMap.ISMs.Add(hash, controller);
	}
	
	return hash;
}
