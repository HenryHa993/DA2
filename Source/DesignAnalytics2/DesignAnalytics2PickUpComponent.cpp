// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesignAnalytics2PickUpComponent.h"

UDesignAnalytics2PickUpComponent::UDesignAnalytics2PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UDesignAnalytics2PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UDesignAnalytics2PickUpComponent::OnSphereBeginOverlap);
}

void UDesignAnalytics2PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ADesignAnalytics2Character* Character = Cast<ADesignAnalytics2Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
