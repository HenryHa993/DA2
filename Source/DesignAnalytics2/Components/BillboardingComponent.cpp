// Fill out your copyright notice in the Description page of Project Settings.


#include "BillboardingComponent.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UBillboardingComponent::UBillboardingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBillboardingComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	OwningActor = GetOwner();
}


// Called every frame
void UBillboardingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerLocation = PlayerPawn->GetActorLocation();
	FVector ownerLocation = OwningActor->GetActorLocation();

	FRotator lookRotation = UKismetMathLibrary::FindLookAtRotation(ownerLocation, playerLocation);

	OwningActor->SetActorRotation(lookRotation);
}

