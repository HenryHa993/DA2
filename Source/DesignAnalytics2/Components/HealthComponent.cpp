// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Damage(float damage)
{
	CurrentHealth -= damage;
	if(CurrentHealth <= 0)
	{
		Death();
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Enemy took %f damage."), damage);
	OnHealthChangedDelegate.Broadcast(CurrentHealth);
	OnDamagedDelegate.Broadcast(damage);
}

void UHealthComponent::SetHealth(float health)
{
	CurrentHealth = health;
	OnHealthChangedDelegate.Broadcast(CurrentHealth);
}

void UHealthComponent::Death()
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy died."));
	OnDeathDelegate.Broadcast();
}

