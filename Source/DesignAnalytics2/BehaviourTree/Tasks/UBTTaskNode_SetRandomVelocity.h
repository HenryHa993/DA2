// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTaskNode_SetRandomVelocity.generated.h"

/**
 * 
 */
UCLASS()
class DESIGNANALYTICS2_API UUBTTaskNode_SetRandomVelocity : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
	float VelocityRange = 1000.0f;
};
