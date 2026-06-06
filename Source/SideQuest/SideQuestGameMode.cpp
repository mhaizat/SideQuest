// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideQuestGameMode.h"
#include "SideQuestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideQuestGameMode::ASideQuestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
