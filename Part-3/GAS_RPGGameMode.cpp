// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS_RPGGameMode.h"
#include "GAS_RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAS_RPGGameMode::AGAS_RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
