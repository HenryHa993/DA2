// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTaskNode_SetRandomVelocity.h"

#include "AIController.h"
#include "GameFramework/PawnMovementComponent.h"

EBTNodeResult::Type UUBTTaskNode_SetRandomVelocity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	APawn* pawn = controller->GetPawn();
	UPawnMovementComponent* movementComponent = pawn->GetMovementComponent();

	float xVel = FMath::RandRange(-VelocityRange, VelocityRange);
	float yVel = FMath::RandRange(-VelocityRange, VelocityRange);
	float zVel = FMath::RandRange(-VelocityRange, VelocityRange);

	movementComponent->Velocity = FVector(xVel, yVel, zVel);
	
	return EBTNodeResult::Succeeded;
}
