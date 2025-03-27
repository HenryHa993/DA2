// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTreeComponent");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
}

void AEnemyAIController::BeginPlay()
{
	if(IsValid(BehaviourTree))
	{
		RunBehaviorTree(BehaviourTree);
		BehaviourTreeComponent->StartTree(*BehaviourTree);
	}

	SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	if(IsValid(BlackboardComponent) && IsValid(BehaviourTree))
	{
		BlackboardComponent->InitializeBlackboard(*(BehaviourTree->GetBlackboardAsset()));
	}
	
	Super::OnPossess(InPawn);
	
}
