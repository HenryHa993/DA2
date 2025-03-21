// Copyright Epic Games, Inc. All Rights Reserved.

#include "DA2GameMode.h"
#include "DA2Character.h"
#include "UObject/ConstructorHelpers.h"

ADA2GameMode::ADA2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
