// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DESIGNANALYTICS2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
    UPROPERTY(EditAnywhere, Category="AI")
    UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere, Category="AI")
	UBehaviorTreeComponent* BehaviourTreeComponent;

	UPROPERTY(EditAnywhere, Category="AI")
	UBlackboardComponent* BlackboardComponent;
};
