// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTaskNode_ShootPlayer.h"

#include "AIController.h"
#include "DesignAnalytics2/Enemy/EnemyPawn.h"

EBTNodeResult::Type UUBTTaskNode_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	AEnemyPawn* pawn = Cast<AEnemyPawn>(controller->GetPawn());
	pawn->Fire();
	return EBTNodeResult::Succeeded;
}
