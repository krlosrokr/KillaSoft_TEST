// Copyright Epic Games, Inc. All Rights Reserved.

#include "KillaSoft_TESTGameMode.h"
#include "KillaSoft_TESTCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKillaSoft_TESTGameMode::AKillaSoft_TESTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
