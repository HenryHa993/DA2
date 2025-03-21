// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISMController.h"
#include "FlecsModuleBase.h"
#include "ComponentsModule.generated.h"

struct TestComponent
{
	int Value;
};

struct ISM_Map
{
	TMap<uint32, AISMController*> ISMs; 
};

struct ISM_ControllerRef
{
	AISMController* Value;
};

struct ISM_Hash
{
	int32 Value;
};

struct ISM_Index
{
	int Value;
};

/**
 * 
 */
UCLASS()
class DA2_API UComponentsModule : public UFlecsModuleBase
{
	GENERATED_BODY()

public:
	virtual void Initialise(flecs::world& ecs) override;
};
