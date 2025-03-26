// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesignAnalytics2GameMode.h"
#include "DesignAnalytics2Character.h"
#include "UObject/ConstructorHelpers.h"

ADesignAnalytics2GameMode::ADesignAnalytics2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
