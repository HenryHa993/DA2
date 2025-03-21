// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemsManager.h"

#include "ComponentsModule.h"
#include "UnrealFlecsSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASystemsManager::ASystemsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASystemsManager::BeginPlay()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UUnrealFlecsSubsystem* flecsSubsystem = gameInstance->GetSubsystem<UUnrealFlecsSubsystem>();
	ECS = flecsSubsystem->GetEcsWorld();
	
	TestSystem = ECS->system<TestComponent>("TestSystem").each([](TestComponent& t)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entity %d"), t.Value);
	});
	Super::BeginPlay();
}

// Called every frame
void ASystemsManager::Tick(float DeltaTime)
{
	TestSystem.run();
	Super::Tick(DeltaTime);
}
