// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarmotteUnrealGDGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMarmotteUnrealGDGameMode::AMarmotteUnrealGDGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
