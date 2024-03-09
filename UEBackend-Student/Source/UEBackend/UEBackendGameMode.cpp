// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEBackendGameMode.h"
#include "UEBackendCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEBackendGameMode::AUEBackendGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
